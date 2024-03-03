// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnomalyManager.generated.h"

UCLASS()
class ABERRATION_API AAnomalyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AAnomalyManager();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	
};
