// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aberrations/AberrationBase.h"
#include "AberrationMovement.generated.h"

/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationMovement : public AAberrationBase
{
	GENERATED_BODY()
public:
	AAberrationMovement();
protected:
	virtual void Tick(float DeltaTime) override;
private:
	virtual void Activate() override;
	virtual void Deactivate() override;

	float Speed = 1.f;
	
	UPROPERTY(EditAnywhere, Category="Aberration")
	float DefaultSpeed = 1.f;
	UPROPERTY(EditAnywhere, Category="Aberration")
	float SpeedMultiplier = 1.f;
	
	UPROPERTY(EditAnywhere, Category="Aberration")
	float StartXPosition = 200.f;

	UPROPERTY(EditAnywhere, Category="Aberration")
	float FinalXPosition = -200.f;

	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
};
