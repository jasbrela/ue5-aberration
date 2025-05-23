// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AberrationSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ABERRATION_API UAberrationSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UAberrationSaveGame();

	/*UPROPERTY(EditAnywhere)
	TArray<int> ExcludedAberrations;

	int CompletedRuns = 0;*/

	UPROPERTY(EditAnywhere)
	float Volume = 1.f;
	UPROPERTY(EditAnywhere)
	float SensX = 1.f;
	UPROPERTY(EditAnywhere)
	float SensY = 1.f;
	UPROPERTY(EditAnywhere)
	float ShakeIntensity = 1.f;
	UPROPERTY(EditAnywhere)
	FString PreferredCulture = "en";
};
