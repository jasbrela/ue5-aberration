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
			AberrationManager->ManagerUpdateAberrationsDelegate.AddDynamic(this, &AAberrationBase::Notify);
		}
    }
}

void AAberrationBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//LOG("Tick");
	
	AberrationTick(DeltaTime);
}

void AAberrationBase::Notify(FActiveAberrations Aberrations)
{
	const bool Contains = Aberrations.Array.Contains(ID);
	
	if (bIsActive == Contains) return;
	
	if (Contains)
	{
		Activate();
	} else
	{
		Deactivate();
	}
	
	bIsActive = Contains;
}

void AAberrationBase::Activate() { }
void AAberrationBase::Deactivate() { }
void AAberrationBase::AberrationTick(float DeltaTime) { }
