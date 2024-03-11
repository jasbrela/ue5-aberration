// Fill out your copyright notice in the Description page of Project Settings.


#include "AberrationGameState.h"

#include "DebugMacros.h"

AAberrationGameState::AAberrationGameState() { }

void AAberrationGameState::SaveSeed(int NewSeed)
{
	Seed = NewSeed;
	RandomStream = FRandomStream(Seed) ;
	LOG_SUCCESS("Seed saved as %i", Seed);
}

int AAberrationGameState::GetSeed() const
{
	return GetRandomStream().GetCurrentSeed();
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
