// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Aberrations/AberrationBase.h"
#include "AberrationVFX.generated.h"

class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationVFX : public AAberrationBase
{
	GENERATED_BODY()

public:
	AAberrationVFX();
private:
	virtual void Activate() override;
	virtual void Deactivate() override;
	UPROPERTY(EditDefaultsOnly, Category = "Aberration")
	UNiagaraComponent* VFX;
};
