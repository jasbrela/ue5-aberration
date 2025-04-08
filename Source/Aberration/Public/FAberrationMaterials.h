#pragma once

#include "CoreMinimal.h"
#include "FAberrationMaterials.generated.h"

USTRUCT(BlueprintType)
struct FAberrationMaterials
{
	GENERATED_BODY()
	
public:
	FAberrationMaterials();
	
	UPROPERTY(EditAnywhere)
	int MaterialIndex = 0;
	
    UPROPERTY(EditAnywhere)
    UMaterialInterface* DefaultMaterial;
    	
    UPROPERTY(EditAnywhere)
    UMaterialInterface* ChangedMaterial;
	
    UPROPERTY(EditAnywhere)
    FName MeshComponentName;

	UPROPERTY()
	UStaticMeshComponent* MeshComponent;
};

inline FAberrationMaterials::FAberrationMaterials()
{
	
}
