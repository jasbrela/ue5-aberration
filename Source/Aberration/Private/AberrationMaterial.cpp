// Fill out your copyright notice in the Description page of Project Settings.


#include "AberrationMaterial.h"

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
	//LOG("Activated");
	Mesh->SetMaterial(MaterialIndex, ChangedMaterial);
}

void AAberrationMaterial::Deactivate()
{
	//LOG("Deactivated");
	Mesh->SetMaterial(MaterialIndex, DefaultMaterial);
}
