// Copyright (c) 2024, Jasbrela. All rights reserved.


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