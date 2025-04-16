// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Aberrations/AberrationBase.h"
#include "AberrationFloating.generated.h"

/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationFloating : public AAberrationBase
{
	GENERATED_BODY()
public:
	AAberrationFloating();
	virtual void Activate() override;
	virtual void Deactivate() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void AberrationTick(float DeltaTime) override;
	
private:
	float TransformedSin(float Alpha) const;
	float TransformedCos(float Alpha) const;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	
	FVector DefaultPosition = FVector::Zero();
	FRotator DefaultRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, Category="Aberration")
	float Amplitude = 1.f;

	UPROPERTY(EditAnywhere, Category="Aberration")
	float Speed = 1.f;
	
	UPROPERTY(VisibleInstanceOnly, Category="Aberration")
	float RunningTime = 0.f;
};
