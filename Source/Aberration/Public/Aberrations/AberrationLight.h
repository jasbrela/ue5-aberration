// Copyright (c) 2024, Jasbrela. All rights reserved.

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
	virtual void Activate() override;
	virtual void Deactivate() override;
	
private:
	UPROPERTY(EditInstanceOnly, Category="Aberration")
	ALight* Light;

	UPROPERTY(EditDefaultsOnly, Category="Aberration")
	float AbnormalIntensity;
	float DefaultIntensity = 2.f;
};
