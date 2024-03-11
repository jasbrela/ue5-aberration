// Fill out your copyright notice in the Description page of Project Settings.


#include "AberrationManager.h"

#include "AberrationGameState.h"
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

FActiveAberrations AAberrationManager::GetLastActiveAberrations()
{
	const int LastCoach = CurrentCoach - 1;
	
	if (CoachAberrations.Num() == 0 || LastCoach < 0 || LastCoach >= CoachAberrations.Num()) return FActiveAberrations();
	return CoachAberrations[LastCoach];
}

TArray<FAberrationData*> AAberrationManager::GetOtherThanActiveAberrations()
{
	return OtherThanActiveAberrations;
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
			const int GeneratedSeed = bOverrideSeed ? Seed : FMath::RandRange(10000, 99999);
			State->SaveSeed(GeneratedSeed);
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
	LOG_SUCCESS("Player changed from coach %i to coach %i", CurrentCoach, CurrentCoach + Change);
	CurrentCoach += Change;
	
	GenerateNextCoachAberrations();
}

bool AAberrationManager::WasLastCoach() const
{
	return CurrentCoach > NumberOfCoaches;
}

void AAberrationManager::UpdateUnlockedAberrations()
{
	for (const FAberrationData* Data : AberrationsData)
	{
		if (Data->UnlockAfterCoach == CurrentCoach)
		{
			UnlockedAberrations.AddUnique(Data->ID);
			AvailableAberrations.AddUnique(Data->ID);
		}
	}	
}

void AAberrationManager::GenerateNextCoachAberrations()
{
	UpdateUnlockedAberrations();

	//LOG("CoachAberrations: %i", CoachAberrations.Num());
	
	if (CurrentCoach >= CoachAberrations.Num())
	{
		CoachAberrations.Add(FActiveAberrations());

		const int GenerateAberrations = RandomStream.RandRange(0, 2); // 0 false, 1 true
		
		if (GenerateAberrations > 0)
		{
			if (AvailableAberrations.Num() == 0)
			{
				LOG_WARNING("No available aberrations found.");
			} else
			{
				LOG_WARNING("[%i] Aberration generated.", CurrentCoach);
				const int RandomAberration = AvailableAberrations[RandomStream.RandRange(0, AvailableAberrations.Num() - 1)];

				AvailableAberrations.Remove(RandomAberration);
				OtherThanActiveAberrations = AberrationsData;
				OtherThanActiveAberrations.RemoveAll([RandomAberration](const FAberrationData* Aberration) {
					return Aberration->ID == RandomAberration;
				});

				if (CoachAberrations[CurrentCoach].Array.Num() > 0) CoachAberrations[CurrentCoach].Array.Empty();
				
				CoachAberrations[CurrentCoach].Array.AddUnique(RandomAberration);
			}
		} else
		{
			LOG_WARNING("[%i] No aberration generated.", CurrentCoach);
		}
	}
	
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

