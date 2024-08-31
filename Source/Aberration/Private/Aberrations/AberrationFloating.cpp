// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationFloating.h"

AAberrationFloating::AAberrationFloating()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void AAberrationFloating::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);

	DefaultPosition = GetActorLocation();
	DefaultRotation = GetActorRotation();
}

void AAberrationFloating::AberrationTick(float DeltaTime)
{
	const float Sin = TransformedSin(RunningTime);
	const float Cos = TransformedCos(RunningTime);
	
	RunningTime += DeltaTime;
	
	AddActorWorldOffset(FVector(0, 0, Sin));
	AddActorWorldRotation(FRotator(Cos, Sin, 0));
}

void AAberrationFloating::Activate()
{
	SetActorTickEnabled(true);
}

void AAberrationFloating::Deactivate()
{
	SetActorTickEnabled(false);

	SetActorLocation(DefaultPosition);
	SetActorRotation(DefaultRotation);
}

float AAberrationFloating::TransformedSin(const float Alpha) const
{
	return Amplitude * FMath::Sin(Alpha * Speed);
}

float AAberrationFloating::TransformedCos(const float Alpha) const
{
	return Amplitude * FMath::Cos(Alpha * Speed);
}