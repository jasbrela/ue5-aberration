// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AberrationCharacter.h"
#include "GameFramework/GameStateBase.h"
#include "AberrationGameState.generated.h"

class USettingsViewModel;
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

	void RegisterScoreEntry(float Percentage);
	void ExcludeAberration(int ID, bool bSave = true);

	void ResetExcludedAberrations();
	
	bool GetPassed();
	float GetFinalScore();
	int GetFinalScorePercentage();

	int GetIncorrectAnswers();
	int GetMaxPoints() const;
	void SetCharacter(AAberrationCharacter* AberrationCharacter);

private:
	UPROPERTY()
	USettingsViewModel* SettingsVM;
	
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
	
	UPROPERTY(EditDefaultsOnly)
	USoundClass* SoundClass;
	
	UPROPERTY(EditDefaultsOnly)
	USoundMix* SoundClassMix;

	AAberrationCharacter* Character;
};
