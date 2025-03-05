// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "AberrationGameState.h"

#include "AberrationSaveGame.h"
#include "DebugMacros.h"
#include "Kismet/GameplayStatics.h"
#include "UI/SettingsViewModel.h"
#include "Types/MVVMViewModelContext.h"
#include "MVVMGameSubsystem.h"
#include "UI/TerminalViewModel.h"

AAberrationGameState::AAberrationGameState() { }

void AAberrationGameState::IncreaseCompletedRuns()
{
	CompletedRuns++;
	LOG_SUCCESS("Completed Run: %i", CompletedRuns);
	ResetExcludedAberrations();
}

UAberrationSaveGame* AAberrationGameState::LoadGame()
{
	/*if (bLoadedGame)
	{
		return LoadedGame;
	} */
	
	LoadedGame = Cast<UAberrationSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("AberrationExpress"), 0));

	SettingsVM = NewObject<USettingsViewModel>(USettingsViewModel::StaticClass());
	
	
	/*LOG_SUCCESS("Loaded game. %i", LoadedGame->ExcludedAberrations.Num());

	ExcludedAberrations.Empty();

	LOG("From Load");
	for (int i = 0; i < LoadedGame->ExcludedAberrations.Num(); i++)
	{
		ExcludeAberration(LoadedGame->ExcludedAberrations[i], false);
	}
	
	CompletedRuns = LoadedGame->CompletedRuns;*/
	bLoadedGame = LoadedGame != nullptr;
	
	if (bLoadedGame)
	{
		SettingsVM->SetVolume(LoadedGame->Volume);
		SettingsVM->SetSensY(LoadedGame->SensY);
		SettingsVM->SetSensX(LoadedGame->SensX);

		Character->SetSensX(LoadedGame->SensX);
		Character->SetSensY(LoadedGame->SensY);

		UGameplayStatics::SetSoundMixClassOverride(this, SoundClassMix, SoundClass, FMath::Clamp(LoadedGame->Volume, 0, 1));
	}
	
	FMVVMViewModelContext Context;
	Context.ContextClass = USettingsViewModel::StaticClass();
	Context.ContextName = TEXT("SettingsVM");
				
	const UMVVMGameSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UMVVMGameSubsystem>();
	Subsystem->GetViewModelCollection()->AddViewModelInstance(Context, SettingsVM);

	UE_LOG(LogTemp, Warning, TEXT("Set up Settings MV"));
	
	if (LoadedGame == nullptr)
	{
		LOG_ERROR("Failed to load game");
		return nullptr;
	}

	return LoadedGame;
}

void AAberrationGameState::SaveSeed(const int NewSeed)
{
	Seed = NewSeed;
	RandomStream = FRandomStream(Seed);
	LOG_SUCCESS("Seed saved as %i", Seed);
	
	if (TerminalVM)
	{
		TerminalVM->SetSeed(Seed);
	}
}

int AAberrationGameState::GetSeed() const
{
	return GetRandomStream().GetCurrentSeed();
}

void AAberrationGameState::SaveGame()
{
	UAberrationSaveGame* Save = Cast<UAberrationSaveGame>(UGameplayStatics::CreateSaveGameObject(UAberrationSaveGame::StaticClass()));

	Save->Volume = SettingsVM->GetVolume();
	Save->SensX = SettingsVM->GetSensX();
	Save->SensY = SettingsVM->GetSensY();
	
	Character->SetSensX(LoadedGame->SensX);
	Character->SetSensY(LoadedGame->SensY);
	UGameplayStatics::SetSoundMixClassOverride(this, SoundClassMix, SoundClass, FMath::Clamp(SettingsVM->GetVolume(), 0, 1));
	
	LOG("Volume set to %f / Sens X set to %f / Sens Y set to %f", Save->Volume, Save->SensX, Save->SensY);

	/*Save->ExcludedAberrations.Empty();

	for (int i = 0; i < ExcludedAberrations.Num(); i++)
	{
		Save->ExcludedAberrations.AddUnique(ExcludedAberrations[i]);
	}
	
	Save->CompletedRuns = CompletedRuns;*/

	const bool Success = UGameplayStatics::SaveGameToSlot(Save, TEXT("AberrationExpress"), 0);
	
	if (Success)
	{
		LOG_SUCCESS("Saved. %i", ExcludedAberrations.Num());
	} else
	{
		LOG_ERROR("Failed to save game.");
	}
}

void AAberrationGameState::SetTerminalVM(UTerminalViewModel* VM)
{
	TerminalVM = VM;
	TerminalVM->SetSeed(Seed);
}

FRandomStream AAberrationGameState::GetRandomStream() const
{
	return RandomStream;
}

void AAberrationGameState::RegisterScoreEntry(const float Percentage)
{
	Percentages.Add(Percentage);
	//LOG_SUCCESS("New score entry registered: %f", Percentage);
}

void AAberrationGameState::ExcludeAberration(const int ID, const bool bSave)
{
	if (ExcludedAberrations.Contains(ID)) return;
	
	ExcludedAberrations.AddUnique(ID);

	if (!bSave)
	{
		LOG("Excluded: %i", ID);
	}

	//LOG("Push new aberration: %i (%i), %s", ID, ExcludedAberrations.Num(), bSave ? TEXT("true") : TEXT("false"));
	if (bSave) SaveGame();
}

void AAberrationGameState::ResetExcludedAberrations()
{
	ExcludedAberrations.Empty();
}

bool AAberrationGameState::GetPassed()
{
	return GetFinalScorePercentage() >= 80;
}

float AAberrationGameState::GetFinalScore()
{
	float Sum = 0.f;
	
	for (int i = 0; i < Percentages.Num(); i++)
	{
		Sum += Percentages[i];
	}
	
	return Sum;
}

int AAberrationGameState::GetFinalScorePercentage()
{
	const float Result = GetFinalScore()/static_cast<float>(Percentages.Num());
	//LOG("%f / %i = %i", GetFinalScore(), Percentages.Num(), FMath::RoundToInt(Result * 100.f));	
	return FMath::RoundToInt(Result * 100.f);
}

int AAberrationGameState::GetIncorrectAnswers()
{
	int Incorrect = 0;
	
	for (int i = 0; i < Percentages.Num(); i++)
	{
		if (Percentages[i] < 0.1)// 0.000
		{
			Incorrect += 3;
		}
		if (Percentages[i] < 0.4) // 0.3333
		{
			Incorrect += 2;
		} else if (Percentages[i] < 0.7) // 0.67
		{
			Incorrect++;
		}
	}
	return Incorrect;
}

int AAberrationGameState::GetMaxPoints() const
{
	return Percentages.Num();
}

void AAberrationGameState::SetCharacter(AAberrationCharacter* AberrationCharacter)
{
	Character = AberrationCharacter;
}
