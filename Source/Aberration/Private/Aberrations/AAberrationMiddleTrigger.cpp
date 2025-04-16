// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AAberrationMiddleTrigger.h"

#include "Components/BoxComponent.h"

AAAberrationMiddleTrigger::AAAberrationMiddleTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
}

void AAAberrationMiddleTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

void AAAberrationMiddleTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAAberrationMiddleTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: NOTIFY ABERRATION CLASSES
}