// Copyright (c) 2024, Jasbrela. All rights reserved.


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

