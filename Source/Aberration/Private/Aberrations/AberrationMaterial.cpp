// Fill out your copyright notice in the Description page of Project Settings.


#include "Aberrations/AberrationMaterial.h"

AAberrationMaterial::AAberrationMaterial() {

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void AAberrationMaterial::BeginPlay()
{
	Super::BeginPlay();
}

void AAberrationMaterial::Activate()
{
	Mesh->SetMaterial(MaterialIndex, ChangedMaterial);
}

void AAberrationMaterial::Deactivate()
{
	Mesh->SetMaterial(MaterialIndex, DefaultMaterial);
}