// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Vestibule.h"

#include "AberrationManager.h"
#include "AberrationCharacter.h"
#include "DebugMacros.h"
#include "TrainDoor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AVestibule::AVestibule()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(100, 200, 150));
	
	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	SetRootComponent(BoxCollision);
	//BoxCollision->SetupAttachment(RootComponent);
}

void AVestibule::ToggleTrigger(bool Enable)
{
	//LOG("CanTrigger: %hs", Enable ? "true" : "false");
	bCanTrigger = Enable;
}

void AVestibule::BeginPlay()
{
	Super::BeginPlay();

	Location = GetActorLocation();

	if (bCanTeleport)
	{
		if (TeleportValue == 0)
		{
			LOG_WARNING("TeleportValue is set to 0. This may cause errors.");
		}
		if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), AAberrationManager::StaticClass()); Actor != nullptr)
		{
			if (AAberrationManager* Manager = Cast<AAberrationManager>(Actor))
			{
				AberrationManager = Manager;
				Manager->SetFrontVestibule(this);
			}
		}
		
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
		//LOG("Registered OnBeginOverlap");
	}

}

void AVestibule::ForceCloseDoor()
{
	Door->ForceCloseDoor();
}

void AVestibule::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bCanTeleport) return;
	
	if (!bCanTrigger)
	{
		LOG_ERROR("CanTrigger is false");
		return;
	}
	
	if (!Cast<AAberrationCharacter>(OtherActor)) return;

	ToggleTrigger(false);
	
	//LOG("Overlapped with %s", *OtherActor->GetActorLabel());

	const FVector OtherLocation = OtherActor->GetActorLocation();
	const FVector NewLocation = /*TeleportTo->GetActorLocation();*/OtherVestibule->GetRelativePosition(GetOffset(OtherActor));

	if (AberrationManager)
	{
		AberrationManager->ChangeCoach(TeleportValue);
	}
	
	OtherActor->SetActorLocation(FVector(NewLocation.X, NewLocation.Y, OtherLocation.Z));
	
	Door->ForceCloseDoor();
}

FVector AVestibule::GetRelativePosition(const FVector& Offset) const
{
	return Location + Offset;
}

FVector AVestibule::GetOffset(const AActor* Actor) const
{
	return Actor->GetActorLocation() - Location;
}

void AVestibule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

