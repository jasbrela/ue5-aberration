// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aberrations/AberrationBase.h"
#include "AberrationVisibility.generated.h"

/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationVisibility : public AAberrationBase
{
	GENERATED_BODY()
public:
	AAberrationVisibility();
private:
	virtual void Activate() override;
	virtual void Deactivate() override;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="Aberration")
	bool bReversedBehaviour = false;
};
