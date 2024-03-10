// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AberrationGameState.generated.h"

/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AAberrationGameState();
	
	void GenerateSeed();
	int GetSeed();
	FRandomStream GetRandomStream();

	void RegisterScoreEntry(float Percentage);

	TArray<float> Percentages;

private:
	FRandomStream RandomStream;
	
	UPROPERTY(EditAnywhere)
	int Seed = -1;
	
	// If checked, game will always run using the "Seed" value.
	UPROPERTY(EditAnywhere)
	bool OverrideSeed = false;
};
