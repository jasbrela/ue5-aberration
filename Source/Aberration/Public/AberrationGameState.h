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
	
	void SaveSeed(int NewSeed);
	int GetSeed() const;
	FRandomStream GetRandomStream() const;

	void RegisterScoreEntry(float Percentage);
	bool GetPassed();
	float GetFinalScore();
	int GetFinalScorePercentage();

	int GetIncorrectAnswers();
	int GetMaxPoints() const;

	TArray<float> Percentages;

private:
	FRandomStream RandomStream;
	
	UPROPERTY()
	int Seed = 0;
};
