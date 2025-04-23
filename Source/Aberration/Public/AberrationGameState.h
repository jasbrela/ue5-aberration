// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AberrationCharacter.h"
#include "GameFramework/GameStateBase.h"
#include "UI/SettingsViewModel.h"
#include "AberrationGameState.generated.h"

class FOnChangeShakeIntensityDelegate;
class FOnChangeShakeIntensity;
class UTerminalViewModel;
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

	UPROPERTY()
	USettingsViewModel* SettingsVM;
	
	void IncreaseCompletedRuns();
	UAberrationSaveGame* LoadGame();
	void SaveSettings();
	void SaveGame();

	void SetTerminalVM(UTerminalViewModel* VM);
	void SaveSeed(int NewSeed);
	int GetSeed() const;
	FRandomStream GetRandomStream() const;

	void RegisterScoreEntry(float Percentage);
	void ExcludeAberration(int ID, bool bSave = true);

	void ResetExcludedAberrations();
	
	bool GetPassed();
	float GetFinalScore();
	int GetFinalScorePercentage();
	
	void SetCharacter(AAberrationCharacter* AberrationCharacter);

private:
	UPROPERTY()
	UTerminalViewModel* TerminalVM;
	
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

	UPROPERTY()
	AAberrationCharacter* Character;
};
