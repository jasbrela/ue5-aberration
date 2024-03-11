// Fill out your copyright notice in the Description page of Project Settings.


#include "Aberrations/AberrationMesh.h"

AAberrationMesh::AAberrationMesh()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void AAberrationMesh::Activate()
{
	Mesh->SetStaticMesh(OtherMesh);
}

void AAberrationMesh::Deactivate()
{
	Mesh->SetStaticMesh(DefaultMesh);
}

