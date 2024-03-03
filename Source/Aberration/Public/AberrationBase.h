// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vestibule.h"
#include "GameFramework/Actor.h"
#include "AberrationBase.generated.h"

UCLASS(Abstract)
class ABERRATION_API AAberrationBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AAberrationBase();

private:
	UFUNCTION()
	virtual void Notify();
	
	FOnPlayerChangeCoachDelegate PlayerChangeCoachDelegate;
};
