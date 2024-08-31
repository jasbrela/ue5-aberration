// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationVisibility.h"

AAberrationVisibility::AAberrationVisibility()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void AAberrationVisibility::Activate()
{
	Mesh->SetVisibility(!bReversedBehaviour, true);
}

void AAberrationVisibility::Deactivate()
{
	Mesh->SetVisibility(bReversedBehaviour, true);
}