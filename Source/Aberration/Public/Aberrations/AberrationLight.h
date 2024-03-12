// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aberrations/AberrationBase.h"
#include "AberrationLight.generated.h"

class ALight;
class UPointLightComponent;
/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationLight : public AAberrationBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	AAberrationLight();
private:
	virtual void Activate() override;
	virtual void Deactivate() override;

	UPROPERTY(EditInstanceOnly, Category="Aberration")
	ALight* Light;

	UPROPERTY(EditDefaultsOnly, Category="Aberration")
	float AbnormalIntensity;
	float DefaultIntensity = 2.f;
};
