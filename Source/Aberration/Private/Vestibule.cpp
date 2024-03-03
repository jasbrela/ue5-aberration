// Fill out your copyright notice in the Description page of Project Settings.


#include "Vestibule.h"

#include "AberrationManager.h"
#include "Aberration/AberrationCharacter.h"
#include "Aberration/DebugMacros.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AVestibule::AVestibule()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
}

void AVestibule::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), AAberrationManager::StaticClass()); Actor != nullptr)
	{
		if (AAberrationManager* Manager = Cast<AAberrationManager>(Actor))
		{
			AberrationManager = Manager;
		}
	}
	
	if (TeleportValue == 0)
	{
		LOG_WARNING("TeleportValue is set to 0. This may cause errors.");
		
	}
	if (bCanTeleport)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
		//LOG("Registered OnBeginOverlap");
	}

	Location = GetActorLocation();
}

void AVestibule::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<AAberrationCharacter>(OtherActor)) return;
	
	LOG("Overlapped with %s", *OtherActor->GetActorLabel());

	const FVector OtherLocation = OtherActor->GetActorLocation();
	const FVector NewLocation = OtherVestibule->GetRelativePosition(GetOffset(OtherActor));

	if (AberrationManager)
	{
		AberrationManager->ChangeCoach(TeleportValue);
	}
	
	OtherActor->SetActorLocation(FVector(NewLocation.X, NewLocation.Y, OtherLocation.Z));
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

