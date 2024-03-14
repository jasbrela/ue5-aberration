// Fill out your copyright notice in the Description page of Project Settings.


#include "AberrationGameState.h"

#include "AberrationSaveGame.h"
#include "DebugMacros.h"
#include "Kismet/GameplayStatics.h"

AAberrationGameState::AAberrationGameState() { }

TArray<int> AAberrationGameState::GetExcludedAberrations()
{
	return ExcludedAberrations;
}

void AAberrationGameState::IncreaseCompletedRuns()
{
	CompletedRuns++;
	LOG_SUCCESS("Completed Run: %i", CompletedRuns);
	ExcludedAberrations.Empty();
}

UAberrationSaveGame* AAberrationGameState::LoadGame()
{
	if (LoadedGame == nullptr)
	{
		LoadedGame = Cast<UAberrationSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("AberrationExpress"), 0));

		if (LoadedGame == nullptr)
		{
			LOG_ERROR("Failed to load game");
			return LoadedGame;
		}
		LOG_SUCCESS("Loaded game. %i", LoadedGame->ExcludedAberrations.Num());
	}

	CompletedRuns = LoadedGame->CompletedRuns;

	return LoadedGame;

}

void AAberrationGameState::SaveSeed(int NewSeed)
{
	Seed = NewSeed;
	RandomStream = FRandomStream(Seed) ;
	LOG_SUCCESS("Seed saved as %i", Seed);
}

void AAberrationGameState::SaveVolume(float Value)
{
	Volume = Value;
}

void AAberrationGameState::SaveSensX(float X)
{
	SensX = X;
}

void AAberrationGameState::SaveSensY(float Y)
{
	SensY = Y;
}

int AAberrationGameState::GetSeed() const
{
	return GetRandomStream().GetCurrentSeed();
}

void AAberrationGameState::SaveGame()
{
	UAberrationSaveGame* Save = Cast<UAberrationSaveGame>(UGameplayStatics::CreateSaveGameObject(UAberrationSaveGame::StaticClass()));

	Save->Volume = Volume;
	Save->SensX = SensX;
	Save->SensY = SensY;
	Save->ExcludedAberrations = ExcludedAberrations;
	Save->CompletedRuns = CompletedRuns;

	const bool Success = UGameplayStatics::SaveGameToSlot(Save, TEXT("AberrationExpress"), 0);
	
	if (Success)
	{
		LOG_SUCCESS("Saved. %i", LoadedGame->ExcludedAberrations.Num());
	} else
	{
		LOG_ERROR("Failed to save game.");
	}
}

FRandomStream AAberrationGameState::GetRandomStream() const
{
	return RandomStream;
}

void AAberrationGameState::RegisterScoreEntry(const float Percentage)
{
	Percentages.Push(Percentage);
	LOG_SUCCESS("New score entry registered: %f", Percentage);
}

void AAberrationGameState::ExcludeAberrationEntry(int ID)
{
	ExcludedAberrations.Push(ID);
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
