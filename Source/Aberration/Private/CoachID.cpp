// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "CoachID.h"

ACoachID::ACoachID()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void ACoachID::BeginPlay()
{
	Super::BeginPlay();
}

void ACoachID::UpdateMaterial(int CurrentCoach)
{
	if (Materials.Num() > CurrentCoach)
	{
		Mesh->SetMaterial(0, Materials[CurrentCoach]);
	}
}

void ACoachID::Hide() const
{
	Mesh->SetVisibility(false);
}

