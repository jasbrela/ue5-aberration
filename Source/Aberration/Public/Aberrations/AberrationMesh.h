// Copyright (c) 2024, Jasbrela. All rights reserved.

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
	virtual void Activate() override;
    virtual void Deactivate() override;
    
private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* DefaultMesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* OtherMesh;
};
