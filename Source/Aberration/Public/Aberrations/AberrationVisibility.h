// Copyright (c) 2024, Jasbrela. All rights reserved.

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
	virtual void BeginPlay() override;
	virtual void Activate() override;
	virtual void Deactivate() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="Aberration")
	bool bReversedBehaviour = false;
	
	UPROPERTY(EditInstanceOnly, Category="Aberration")
	int OverrideID = -1;
	
	UPROPERTY(EditInstanceOnly, Category="Aberration")
	AActor* OverrideActor;
};
