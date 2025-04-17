// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Aberrations/AberrationBase.h"
#include "AberrationAnimation.generated.h"

/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationAnimation : public AAberrationBase
{
	GENERATED_BODY()
public:
	AAberrationAnimation();
	virtual void Activate() override;
	virtual void Deactivate() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void AberrationTick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	
	FVector DefaultPosition = FVector::Zero();
	FRotator DefaultRotation = FRotator::ZeroRotator;
	
	UPROPERTY(EditAnywhere, Category="Aberration")
	FVector DesiredPosition;
	
	UPROPERTY(EditAnywhere, Category="Aberration")
	FRotator DesiredRotation;

	UPROPERTY(EditAnywhere, Category="Aberration")
	float Duration = 1.f;
	
	UPROPERTY(VisibleInstanceOnly, Category="Aberration")
	float RunningTime = 0.f;
	UPROPERTY(VisibleInstanceOnly, Category="Aberration")
	float Alpha = 0.f;
};
