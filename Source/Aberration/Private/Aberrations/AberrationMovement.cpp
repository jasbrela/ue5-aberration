// Fill out your copyright notice in the Description page of Project Settings.


#include "Aberrations/AberrationMovement.h"

AAberrationMovement::AAberrationMovement()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void AAberrationMovement::BeginPlay()
{
	Super::BeginPlay();
	
	Speed = DefaultSpeed;
}

void AAberrationMovement::AberrationTick(float DeltaTime)
{
	const bool GoingForward = Speed > 0;
	const float CurrentLocation = Mesh->GetRelativeLocation().X;
	const float FinalLocation = GoingForward ? FinalXPosition : StartXPosition;
	const float StartLocation = GoingForward ? StartXPosition : FinalXPosition;

	const bool NearlyEqual = FMath::IsNearlyEqual(CurrentLocation, FinalLocation, 1.f);
	const bool OffLimits = (GoingForward && CurrentLocation > FinalLocation) || (!GoingForward && CurrentLocation < FinalLocation);

	if (NearlyEqual || OffLimits)
	{
		const FVector Location = Mesh->GetRelativeLocation();
		Mesh->SetRelativeLocation(FVector(StartLocation, Location.Y, Location.Z));
	}
	
	const float XOffsetToAdd = Speed * DeltaTime;
	
	const FVector LocationToAdd = FVector(XOffsetToAdd, 0, 0);
	Mesh->AddRelativeLocation(LocationToAdd);
}

void AAberrationMovement::Activate()
{
	Speed *= SpeedMultiplier;

	const FVector Location = Mesh->GetRelativeLocation();
	Mesh->SetRelativeLocation(FVector(Location.X, Speed > 0 ? StartXPosition : FinalXPosition, Location.Z));
}

void AAberrationMovement::Deactivate()
{
	Speed = DefaultSpeed;
	
	const FVector Location = Mesh->GetRelativeLocation();
	Mesh->SetRelativeLocation(FVector(Location.X, Speed > 0 ? StartXPosition : FinalXPosition, Location.Z));
}