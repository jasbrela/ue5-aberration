// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationVisibility.h"

#include "DebugMacros.h"

AAberrationVisibility::AAberrationVisibility()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void AAberrationVisibility::BeginPlay()
{
	Super::BeginPlay();

	if (OverrideID >= 0) ID = OverrideID;

	if (OverrideActor != nullptr)
	{
		UStaticMeshComponent* MeshComponent = OverrideActor->FindComponentByClass<UStaticMeshComponent>();
		if (MeshComponent != nullptr)
		{
			Mesh = MeshComponent;
			//LOG_SUCCESS("AberrationVisibility: Successfully overrode Mesh");
		}
	}
}

void AAberrationVisibility::Activate()
{
	Mesh->SetVisibility(!bReversedBehaviour, true);
}

void AAberrationVisibility::Deactivate()
{
	Mesh->SetVisibility(bReversedBehaviour, true);
}