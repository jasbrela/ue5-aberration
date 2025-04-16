// Copyright (c) 2024, Jasbrela. All rights reserved.

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
	virtual void Activate() override;
	virtual void Deactivate() override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Aberration")
	float ScaleMultiplier = 1.f;

	UPROPERTY(EditDefaultsOnly, Category="Aberration")
	FVector DefaultScale = FVector::One();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly)
	AActor* Override;
};
