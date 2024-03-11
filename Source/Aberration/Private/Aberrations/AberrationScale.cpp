// Fill out your copyright notice in the Description page of Project Settings.


#include "Aberrations/AberrationScale.h"

AAberrationScale::AAberrationScale()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void AAberrationScale::BeginPlay()
{
	Super::BeginPlay();
	DefaultScale = Mesh->GetComponentScale();
}

void AAberrationScale::Activate()
{
	Mesh->SetRelativeScale3D(DefaultScale * ScaleMultiplier);
}

void AAberrationScale::Deactivate()
{
	Mesh->SetRelativeScale3D(DefaultScale);
}