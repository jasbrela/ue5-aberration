// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationVFX.h"

#include "DebugMacros.h"
#include "NiagaraComponent.h"

AAberrationVFX::AAberrationVFX()
{
	PrimaryActorTick.bCanEverTick = false;
	VFX = CreateDefaultSubobject<UNiagaraComponent>("VFX");

	VFX->bAutoActivate = false;

	SetRootComponent(VFX);
}

void AAberrationVFX::Activate()
{
	LOG("AberrationVFX::Activate()");
	VFX->ActivateSystem();
}

void AAberrationVFX::Deactivate()
{
	VFX->DeactivateImmediate();
}