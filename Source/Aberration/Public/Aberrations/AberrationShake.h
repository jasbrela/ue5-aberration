// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Aberrations/AberrationBase.h"
#include "UI/SettingsViewModel.h"
#include "AberrationShake.generated.h"

/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationShake : public AAberrationBase
{
	GENERATED_BODY()
public:
	AAberrationShake();
	virtual void BeginPlay() override;
	virtual void Activate() override;
	virtual void Deactivate() override;
private:
	UPROPERTY()
	AAberrationGameState* State;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aberration")
	TSubclassOf<UCameraShakeBase> CameraShake;
	
	UPROPERTY()
	UCameraShakeBase* ShakeInstance;
};
