// Copyright (c) 2024, Jasbrela. All rights reserved.

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
	virtual void Activate() override;
	virtual void Deactivate() override;

protected:
	virtual void BeginPlay() override;
	
private:
	virtual void AberrationTick(float DeltaTime) override;

	float Speed = 1.f;
	
	UPROPERTY(EditAnywhere, Category="Aberration")
	float DefaultSpeed = 1.f;
	UPROPERTY(EditAnywhere, Category="Aberration")
	float SpeedMultiplier = 1.f;
	
	UPROPERTY(EditAnywhere, Category="Aberration")
	float StartXPosition = 4000.0f;

	UPROPERTY(EditAnywhere, Category="Aberration")
	float FinalXPosition = -2500.0f;

	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
};
