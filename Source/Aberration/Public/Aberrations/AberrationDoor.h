// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aberrations/AberrationBase.h"
#include "AberrationDoor.generated.h"

class ATrainDoor;
/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationDoor : public AAberrationBase
{
	GENERATED_BODY()
public:
	AAberrationDoor();
private:
	virtual void Activate() override;
	virtual void Deactivate() override;

	UPROPERTY(EditInstanceOnly)
	ATrainDoor* Door;
};
