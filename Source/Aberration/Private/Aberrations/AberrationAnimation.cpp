// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationAnimation.h"

AAberrationAnimation::AAberrationAnimation()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void AAberrationAnimation::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);

	DefaultPosition = GetRootComponent()->GetRelativeLocation();
	DefaultRotation = GetRootComponent()->GetRelativeRotation();
}

void AAberrationAnimation::AberrationTick(float DeltaTime)
{
	RunningTime += DeltaTime;

	if (RunningTime >= Duration)
	{
		SetActorRelativeLocation(DesiredPosition);
		SetActorRelativeRotation(DesiredRotation);
		SetActorTickEnabled(false);
		return;
	}

	Alpha = FMath::Clamp(RunningTime / Duration, 0.f, 1.f);
	SetActorRelativeLocation(FMath::Lerp(DefaultPosition, DesiredPosition, Alpha));
	SetActorRelativeRotation(FMath::Lerp(DefaultRotation, DesiredRotation, Alpha));
	
}

void AAberrationAnimation::Activate()
{
	RunningTime = 0;
	SetActorTickEnabled(true);
}

void AAberrationAnimation::Deactivate()
{
	SetActorTickEnabled(false);

	SetActorRelativeLocation(DefaultPosition);
	SetActorRelativeRotation(DefaultRotation);
}