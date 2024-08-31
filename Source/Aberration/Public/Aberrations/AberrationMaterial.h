// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AberrationBase.h"
#include "AberrationMaterial.generated.h"

/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationMaterial : public AAberrationBase
{
	GENERATED_BODY()
	
public:
	AAberrationMaterial();
	
protected:
	virtual void BeginPlay() override;
	
private:
	virtual void Activate() override;
	virtual void Deactivate() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Aberration")
    int MaterialIndex;
	
	UPROPERTY(EditDefaultsOnly, Category="Aberration")
	UMaterialInterface* DefaultMaterial;
	
	UPROPERTY(EditDefaultsOnly, Category="Aberration")
	UMaterialInterface* ChangedMaterial;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	
};
