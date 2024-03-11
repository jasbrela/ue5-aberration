// Fill out your copyright notice in the Description page of Project Settings.


#include "Aberrations/AberrationVisibility.h"

AAberrationVisibility::AAberrationVisibility()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	AAberrationVisibility::Deactivate();
}

void AAberrationVisibility::Activate()
{
	Mesh->SetVisibility(!bReversedBehaviour, true);
}

void AAberrationVisibility::Deactivate()
{
	Mesh->SetVisibility(bReversedBehaviour, true);
}