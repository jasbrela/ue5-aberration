// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AberrationBase.h"
#include "AberrationScale.generated.h"

/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationScale : public AAberrationBase
{
	GENERATED_BODY()

public:
	AAberrationScale();
	
protected:
	virtual void BeginPlay() override;

private:
	virtual void Activate() override;
	virtual void Deactivate() override;

	UPROPERTY(EditDefaultsOnly, Category="Aberration")
	int ScaleMultiplier = 1;

	UPROPERTY(EditDefaultsOnly, Category="Aberration")
	FVector DefaultScale = FVector::One();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
};
