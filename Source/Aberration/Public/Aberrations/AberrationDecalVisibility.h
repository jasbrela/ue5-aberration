// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Aberrations/AberrationBase.h"
#include "AberrationDecalVisibility.generated.h"

/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationDecalVisibility : public AAberrationBase
{
	GENERATED_BODY()
	
public:
	AAberrationDecalVisibility();
	virtual void Activate() override;
	virtual void Deactivate() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	UDecalComponent* Decal;

	UPROPERTY(EditAnywhere, Category="Aberration")
	bool bReversedBehaviour = false;
};
