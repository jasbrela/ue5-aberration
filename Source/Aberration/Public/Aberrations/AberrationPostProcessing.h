// Copyright (c) 2024, Jasbrela. All rights reserved.

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
	virtual void Activate() override;
	virtual void Deactivate() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	UPostProcessComponent* PostProcessComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Bounds;

	bool bReversedBehaviour = false;
};
