// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Aberrations/AberrationBase.h"
#include "AberrationSound.generated.h"
/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationSound : public AAberrationBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	AAberrationSound();
private:
	virtual void Activate() override;
	virtual void Deactivate() override;

	UPROPERTY()
	UAudioComponent* AudioComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Aberration")
	USoundBase* DefaultSFX;
	UPROPERTY(EditDefaultsOnly, Category="Aberration")
	USoundBase* AbnormalSFX;
};
