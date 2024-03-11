// Fill out your copyright notice in the Description page of Project Settings.


#include "Aberrations/AberrationBase.h"

#include "AberrationManager.h"
#include "Kismet/GameplayStatics.h"

AAberrationBase::AAberrationBase() { }

void AAberrationBase::BeginPlay()
{
	Super::BeginPlay();
	
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

void AAberrationBase::Notify(FActiveAberrations Aberrations)
{
	const bool Contains = Aberrations.Array.Contains(ID);
	
	if (bIsActive == Contains) return;
	
	bIsActive = Contains;

	if (bIsActive != bReverseBehaviour)
	{
		Activate();
	}
	else
	{
		Deactivate();
	}
}

void AAberrationBase::Activate() { }

void AAberrationBase::Deactivate() { }
