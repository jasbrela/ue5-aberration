// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationPostProcessing.h"

#include "Components/BoxComponent.h"
#include "Components/PostProcessComponent.h"

AAberrationPostProcessing::AAberrationPostProcessing()
{
	Bounds = CreateDefaultSubobject<UBoxComponent>(TEXT("Bounds"));
	PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessing"));
	PostProcessComponent->bUnbound = false;
	
	SetRootComponent(Bounds);
	PostProcessComponent->SetupAttachment(RootComponent);
}

void AAberrationPostProcessing::Activate()
{
	Bounds->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	PostProcessComponent->bEnabled = !bReversedBehaviour;
}

void AAberrationPostProcessing::Deactivate()
{
	Bounds->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PostProcessComponent->bEnabled = bReversedBehaviour;
}