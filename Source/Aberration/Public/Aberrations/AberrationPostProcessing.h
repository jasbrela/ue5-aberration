// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aberrations/AberrationBase.h"
#include "AberrationPostProcessing.generated.h"

class UPostProcessComponent;
class UBoxComponent;
class APostProcessVolume;
/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationPostProcessing : public AAberrationBase
{
	GENERATED_BODY()
public:
	AAberrationPostProcessing();
	
private:
	virtual void Activate() override;
	virtual void Deactivate() override;

	UPROPERTY(EditDefaultsOnly)
	UPostProcessComponent* PostProcessComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Bounds;

	bool bReversedBehaviour = false;
};
