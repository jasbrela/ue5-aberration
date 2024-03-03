// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AberrationBase.h"
#include "AberrationColor.generated.h"

/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationColor : public AAberrationBase
{
	GENERATED_BODY()
	
public:
	AAberrationColor();
	
protected:
	virtual void BeginPlay() override;
	
private:
	virtual void Notify(FActiveAberrations Aberrations) override;
};
