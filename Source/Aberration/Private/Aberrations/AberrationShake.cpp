// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationShake.h"

#include "DebugMacros.h"
#include "Kismet/GameplayStatics.h"

AAberrationShake::AAberrationShake() { }

void AAberrationShake::BeginPlay()
{
	Super::BeginPlay();
}

void AAberrationShake::Activate()
{
	LOG_SUCCESS("Shake Triggered");
	ShakeInstance = UGameplayStatics::GetPlayerCameraManager(this, 0)->StartCameraShake(CameraShake);
}

void AAberrationShake::Deactivate()
{
	if (ShakeInstance)
	{
		UGameplayStatics::GetPlayerCameraManager(this, 0)->StopCameraShake(ShakeInstance);
	}
}
