// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AberrationManager.h"
#include "GameFramework/Actor.h"
#include "AberrationBase.generated.h"

UCLASS(Abstract)
class ABERRATION_API AAberrationBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AAberrationBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleInstanceOnly)
	AAberrationManager* AberrationManager;

private:
	// The ID of the aberration must match their ID in Aberrations' DataTable
	UPROPERTY(VisibleDefaultsOnly)
	int ID = 0;
	
	UFUNCTION()
	virtual void Notify(FActiveAberrations Aberrations);
};
