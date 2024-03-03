// Fill out your copyright notice in the Description page of Project Settings.


#include "AberrationManager.h"

#include "FActiveAberrations.h"
#include "Aberration/DebugMacros.h"


AAberrationManager::AAberrationManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

FActiveAberrations AAberrationManager::GetActiveAberrations()
{
	if (CurrentCoach >= CoachAberrations.Num()) return FActiveAberrations();
	return CoachAberrations[CurrentCoach];
}

void AAberrationManager::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateSeed();
	GenerateCoachAberrations();
}

void AAberrationManager::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AAberrationManager::ChangeCoach(int Change)
{
	LOG_SUCCESS("Player changed from coach %i to coach %i", CurrentCoach, CurrentCoach + Change);
	CurrentCoach += Change;

	ManagerUpdateAberrationsDelegate.Broadcast(GetActiveAberrations());
}

void AAberrationManager::GenerateSeed()
{
	if (!OverrideSeed)
	{
		Seed = FMath::RandRange(10000, 99999);
	}
	
	RandomStream = FRandomStream(Seed);
	LOG_SUCCESS("Seed set to: %i", Seed);
}

void AAberrationManager::GenerateCoachAberrations()
{
	/*for (const int i : NumberOfCoaches)
	{
		CoachAberrations[i].Array;
	}*/
}

void AAberrationManager::ConvertTable()
{
	const TArray<FName> Names = AberrationsDataTable->GetRowNames();
	const FString Context = TEXT("");
	
	for (int i = 0; i < Names.Num(); i++)
	{
		FAberrationData* Mission = AberrationsDataTable->FindRow<FAberrationData>(Names[i], Context);
		AberrationsData.Add(Mission);
	}
}

