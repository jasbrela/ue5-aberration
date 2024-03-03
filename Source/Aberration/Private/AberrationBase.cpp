// Fill out your copyright notice in the Description page of Project Settings.


#include "AberrationBase.h"

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
			AberrationManager->ManagerUpdateAberrationsDelegate.AddDynamic(this, &AAberrationBase::Notify);
		}
    }
}

void AAberrationBase::Notify(FActiveAberrations Aberrations) { }
