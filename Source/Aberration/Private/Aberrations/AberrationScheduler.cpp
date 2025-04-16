// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationScheduler.h"

#include "DebugMacros.h"

AAberrationScheduler::AAberrationScheduler()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAberrationScheduler::BeginPlay()
{
	if (OverrideID >= 0) ID = OverrideID;
	Super::BeginPlay();
}

void AAberrationScheduler::Trigger()
{
	LOG_SUCCESS("Scheduler Triggered");
	for (int i = 0; i < Aberrations.Num(); i++)
	{
		Aberrations[i]->Activate();
	}
}

void AAberrationScheduler::Activate()
{
	LOG_SUCCESS("Activated Scheduler");
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::Trigger, DelayToTrigger, bLoop);
}

void AAberrationScheduler::Deactivate()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	LOG_SUCCESS("Deactivated Scheduler");
	
	for (int i = 0; i < Aberrations.Num(); i++)
	{
		Aberrations[i]->Deactivate();
	}
}

