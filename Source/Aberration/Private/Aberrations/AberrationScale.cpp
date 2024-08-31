// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationScale.h"

AAberrationScale::AAberrationScale()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void AAberrationScale::BeginPlay()
{
	Super::BeginPlay();
	
	if (Override)
	{
		DefaultScale = Override->GetActorRelativeScale3D();
	} else
	{
		DefaultScale = Mesh->GetComponentScale();
	}
}

void AAberrationScale::Activate()
{
	if (Override)
	{
		Override->SetActorRelativeScale3D(DefaultScale * ScaleMultiplier);
	} else
	{
		Mesh->SetRelativeScale3D(DefaultScale * ScaleMultiplier);
	}
}

void AAberrationScale::Deactivate()
{
	if (Override)
	{
		Override->SetActorRelativeScale3D(DefaultScale);
	} else
	{
		Mesh->SetRelativeScale3D(DefaultScale);
	}
}