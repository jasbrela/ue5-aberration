// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationDecalVisibility.h"

#include "Components/DecalComponent.h"

AAberrationDecalVisibility::AAberrationDecalVisibility()
{
	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	Decal->SetVisibility(false);
	SetRootComponent(Decal);
}

void AAberrationDecalVisibility::Activate()
{
	Decal->SetVisibility(!bReversedBehaviour, true);
}

void AAberrationDecalVisibility::Deactivate()
{
	Decal->SetVisibility(bReversedBehaviour, true);
}