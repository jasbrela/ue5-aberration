// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationMiddleTrigger.h"

#include "AberrationManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AAberrationMiddleTrigger::AAberrationMiddleTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
}

void AAberrationMiddleTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

	if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), AAberrationManager::StaticClass()); Actor != nullptr)
	{
		if (AAberrationManager* AberrationManager = Cast<AAberrationManager>(Actor))
		{
			Manager = AberrationManager;
			AberrationManager->ManagerUpdateAberrationsDelegate.AddDynamic(this, &ThisClass::Activate);
		}
	}
}

void AAberrationMiddleTrigger::Activate(FActiveAberrations _)
{
	bIsActive = true;
}

void AAberrationMiddleTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAberrationMiddleTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsActive) return;
	bIsActive = false;
	
	Manager->PlayerReachedTrainMidpoint.Broadcast(Manager->GetActiveAberrations());
}