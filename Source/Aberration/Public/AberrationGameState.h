// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AberrationGameState.generated.h"

class UAberrationSaveGame;
/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AAberrationGameState();

	void IncreaseCompletedRuns();
	UAberrationSaveGame* LoadGame();
	void SaveGame();
	
	void SaveSeed(int NewSeed);
	int GetSeed() const;
	FRandomStream GetRandomStream() const;
	
	void SaveVolume(float Value);
	void SaveSensX(float X);
	void SaveSensY(float Y);

	void RegisterScoreEntry(float Percentage);
	void ExcludeAberration(int ID, bool bSave = true);

	void ResetExcludedAberrations();
	
	bool GetPassed();
	float GetFinalScore();
	int GetFinalScorePercentage();

	int GetIncorrectAnswers();
	int GetMaxPoints() const;


private:
	bool bLoadedGame;
	FRandomStream RandomStream;
	TArray<float> Percentages;
	TArray<int> ExcludedAberrations;
	
	UPROPERTY()
	UAberrationSaveGame* LoadedGame = nullptr;
	
	UPROPERTY()
	int Seed = 0;

	UPROPERTY()
	int CompletedRuns = 0;

	UPROPERTY()
	float Volume = 1.f;

	UPROPERTY()
	float SensX = 1.f;

	UPROPERTY()
	float SensY = 1.f;
};
