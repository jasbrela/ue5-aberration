// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationBase.h"

#include "AberrationManager.h"
#include "Kismet/GameplayStatics.h"

AAberrationBase::AAberrationBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAberrationBase::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(true);
	
	if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), AAberrationManager::StaticClass()); Actor != nullptr)
    {
	    if (AAberrationManager* Manager = Cast<AAberrationManager>(Actor))
		{
			AberrationManager = Manager;
			//LOG("BeginPlay %s", *GetActorLabel());
			AberrationManager->ManagerUpdateAberrationsDelegate.AddDynamic(this, &ThisClass::NotifyAberrationChanged);
			AberrationManager->PlayerReachedTrainMidpoint.AddDynamic(this, &ThisClass::NotifyMidpointReached);
		}
    }
}

void AAberrationBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//LOG("Tick");
	
	AberrationTick(DeltaTime);
}

void AAberrationBase::NotifyAberrationChanged(FActiveAberrations Aberrations)
{
	const bool bIsChosenAberration = Aberrations.Array.Contains(ID);

	if (bIsActive == bIsChosenAberration) return;
	
	if (bIsActive && !bIsChosenAberration)
	{
		bIsActive = false;
		Deactivate();
		return;
	}

	if (!bWaitUntilMidpointIsReached)
	{
		Activate();
	}
}

void AAberrationBase::NotifyMidpointReached(FActiveAberrations Aberrations)
{
	const bool bIsChosenAberration = Aberrations.Array.Contains(ID);

	if (!bIsChosenAberration) return;
	
	if (bWaitUntilMidpointIsReached)
	{
		Activate();
	}
}

void AAberrationBase::Activate() { }
void AAberrationBase::Deactivate() { }
void AAberrationBase::AberrationTick(float DeltaTime) { }
