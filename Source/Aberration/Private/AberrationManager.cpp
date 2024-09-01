// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "AberrationManager.h"

#include "AberrationGameState.h"
#include "AberrationSaveGame.h"
#include "CoachID.h"
#include "FActiveAberrations.h"
#include "DebugMacros.h"


AAberrationManager::AAberrationManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

FActiveAberrations AAberrationManager::GetActiveAberrations()
{
	if (CoachAberrations.Num() == 0 || CurrentCoach < 0 || CurrentCoach >= CoachAberrations.Num()) return FActiveAberrations();
	return CoachAberrations[CurrentCoach];
}

FActiveAberrations AAberrationManager::GetPreviousActiveAberrations()
{
	const int PreviousCoach = CurrentCoach - 1;
	
	if (CoachAberrations.Num() == 0 || PreviousCoach < 0 || PreviousCoach >= CoachAberrations.Num()) return FActiveAberrations();
	return CoachAberrations[PreviousCoach];
}

TArray<FAberrationData*> AAberrationManager::GetPreviousOtherThanActiveAberrations()
{
	if (PreviousOtherThanActiveAberrations.Num() == 0) return AberrationsData;
	return PreviousOtherThanActiveAberrations;
}

int AAberrationManager::GetCurrentCoach() const
{
	return CurrentCoach;
}

void AAberrationManager::BeginPlay()
{
	Super::BeginPlay();

	GenerateSeed();
	
	ConvertTable();
	
	GetWorldTimerManager().SetTimer(BeginPlayDelayTimerHandle, this, &AAberrationManager::GenerateNextCoachAberrations, .2f, false);
}

void AAberrationManager::GenerateSeed()
{
	if (const UWorld* World = GetWorld())
	{
		if (AAberrationGameState* State = World->GetGameState<AAberrationGameState>())
		{
			AberrationState = State;
			const int GeneratedSeed = bOverrideSeed ? Seed : FMath::RandRange(10000, 99999);
			AberrationState->SaveSeed(GeneratedSeed);
			RandomStream = AberrationState->GetRandomStream();
		}
	}
	else
	{
		RandomStream = FRandomStream(0);
	}
	
}

void AAberrationManager::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AAberrationManager::ChangeCoach(int Change)
{
	//LOG_SUCCESS("Player changed from coach %i to coach %i", CurrentCoach, CurrentCoach + Change);
	
	if (CurrentCoach < CoachAberrations.Num() && !CoachAberrations[CurrentCoach].Array.IsEmpty())
	{
		//LOG("ID: %i", CoachAberrations[CurrentCoach].Array[0]);
		LOG("From Manager");
		AberrationState->ExcludeAberration(CoachAberrations[CurrentCoach].Array[0]);
	}
	
	CurrentCoach += Change;

	if (FrontID)
	{
		if (CurrentCoach >= NumberOfCoaches)
		{
			if (CurrentCoach == NumberOfCoaches) FrontID->Hide();
			else BackID->Hide();
		} else
		{
			FrontID->UpdateMaterial(CurrentCoach+1);
		}
	}
	
	if (BackID) BackID->UpdateMaterial(CurrentCoach);
	
	GenerateNextCoachAberrations();
}

bool AAberrationManager::WasLastCoach() const
{
	return CurrentCoach > NumberOfCoaches;
}

int AAberrationManager::GetNumberOfCoaches() const
{
	return NumberOfCoaches;
}

void AAberrationManager::UpdateUnlockedAberrations()
{
	const UAberrationSaveGame* Save = AberrationState->LoadGame();

	if (Save) ExcludedAberrations = Save->ExcludedAberrations;
	
	for (const FAberrationData* Data : AberrationsData)
	{
		if (Data->UnlockAfterCoach == CurrentCoach)
		{
			if (Save)
			{
				if (!Save->ExcludedAberrations.Contains(Data->ID))
				{
					AvailableAberrations.AddUnique(Data->ID);
					continue;
				}
			} else AvailableAberrations.AddUnique(Data->ID);
			
			UnlockedAberrations.AddUnique(Data->ID);
		}
	}	
}

void AAberrationManager::GenerateNextCoachAberrations()
{
	UpdateUnlockedAberrations();

	//LOG("CoachAberrations: %i", CoachAberrations.Num());
	
	if (CurrentCoach >= CoachAberrations.Num() && CurrentCoach <= NumberOfCoaches)
	{
		CoachAberrations.Add(FActiveAberrations());

		const int GenerateAberrations = RandomStream.RandRange(0, 2); // 0 false, 1 true

		//LOG("Seed: %i", RandomStream.GetCurrentSeed());
		
		if (GenerateAberrations > 0 || GetPreviousActiveAberrations().Array.Num() == 0)
		{
			if (AvailableAberrations.IsEmpty())
			{
				LOG_WARNING("No available aberrations found.");
			} else
			{
				const int RandomAberration = AvailableAberrations[RandomStream.RandRange(0, AvailableAberrations.Num() - 1)];
				
				AvailableAberrations.Remove(RandomAberration);
				
				if (AvailableAberrations.IsEmpty())
				{
					AberrationState->IncreaseCompletedRuns();
					AvailableAberrations = UnlockedAberrations;
				}
				
				PreviousOtherThanActiveAberrations = OtherThanActiveAberrations;
				
				OtherThanActiveAberrations = AberrationsData;
				
				OtherThanActiveAberrations.RemoveAll([RandomAberration](const FAberrationData* Aberration) {
					if (Aberration->ID == RandomAberration)
					{
						LOG_WARNING("Aberration generated: %s", *Aberration->AberrationName);
					}
					
					return Aberration->ID == RandomAberration;
				});

				if (!CoachAberrations[CurrentCoach].Array.IsEmpty()) CoachAberrations[CurrentCoach].Array.Empty();
				
				CoachAberrations[CurrentCoach].Array.AddUnique(RandomAberration);
			}
		} else
		{
			LOG_WARNING("[%i] No aberration generated.", CurrentCoach);
		}
	} else LOG_ERROR("Couldnt generate aberration");
	
	ManagerUpdateAberrationsDelegate.Broadcast(GetActiveAberrations());
}

void AAberrationManager::ConvertTable()
{
	const TArray<FName> Names = AberrationsDataTable->GetRowNames();
	const FString Context = TEXT("");
	
	for (int i = 0; i < Names.Num(); i++)
	{
		FAberrationData* Aberration = AberrationsDataTable->FindRow<FAberrationData>(Names[i], Context);
		AberrationsData.Add(Aberration);
		OtherThanActiveAberrations.Add(Aberration);
	}
}

