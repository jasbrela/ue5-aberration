// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoachID.generated.h"

UCLASS()
class ABERRATION_API ACoachID : public AActor
{
	GENERATED_BODY()
	
public:	
	ACoachID();
	void UpdateMaterial(int CurrentCoach);
	void Hide() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterialInterface*> Materials;
};
