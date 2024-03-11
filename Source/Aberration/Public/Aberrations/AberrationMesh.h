// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aberrations/AberrationBase.h"
#include "AberrationMesh.generated.h"

/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationMesh : public AAberrationBase
{
	GENERATED_BODY()
public:
	AAberrationMesh();
private:
	virtual void Activate() override;
    virtual void Deactivate() override;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* DefaultMesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* OtherMesh;
};
