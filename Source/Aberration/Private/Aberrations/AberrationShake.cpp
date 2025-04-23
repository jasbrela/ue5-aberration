// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationShake.h"

#include "AberrationGameState.h"
#include "DebugMacros.h"
#include "Kismet/GameplayStatics.h"

AAberrationShake::AAberrationShake() { }

void AAberrationShake::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		if (AAberrationGameState* GameState = World->GetGameState<AAberrationGameState>())
		{
			State = GameState;
		}
	}
}

void AAberrationShake::Activate()
{
	ShakeInstance = UGameplayStatics::GetPlayerCameraManager(this, 0)->StartCameraShake(CameraShake, State->SettingsVM->GetShakeIntensity());
}

void AAberrationShake::Deactivate()
{
	if (ShakeInstance)
	{
		UGameplayStatics::GetPlayerCameraManager(this, 0)->StopCameraShake(ShakeInstance);
	}
}
