// Fill out your copyright notice in the Description page of Project Settings.


#include "Vestibule.h"

#include "Aberration/DebugMacros.h"
#include "Components/BoxComponent.h"

FOnPlayerChangeCoachDelegate AVestibule::PlayerChangeCoachDelegate;

AVestibule::AVestibule()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
}

void AVestibule::BeginPlay()
{
	Super::BeginPlay();

	if (bCanTeleport)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
		LOG("Registered OnBeginOverlap");
	}

	Location = GetActorLocation();
}

void AVestibule::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Check if OtherActor is Player
	LOG("Overlapped with %s", *OtherActor->GetName());
	
	FVector OtherLocation = OtherActor->GetActorLocation();
	FVector NewLocation = OtherVestibule->GetRelativePosition(GetOffset(OtherActor));

	PlayerChangeCoachDelegate.Broadcast();
	
	OtherActor->SetActorLocation(FVector(NewLocation.X, NewLocation.Y, OtherLocation.Z));
}

FVector AVestibule::GetRelativePosition(FVector Offset)
{
	return Location + Offset;
}

FVector AVestibule::GetOffset(AActor* Actor)
{
	return Actor->GetActorLocation() - Location;
}

void AVestibule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

