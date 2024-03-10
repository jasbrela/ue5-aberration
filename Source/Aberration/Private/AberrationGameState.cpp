// Fill out your copyright notice in the Description page of Project Settings.


#include "AberrationGameState.h"

#include "DebugMacros.h"

AAberrationGameState::AAberrationGameState()
{
	GenerateSeed();
}

void AAberrationGameState::GenerateSeed()
{
	if (!OverrideSeed)
	{
		Seed = FMath::RandRange(10000, 99999);
	}
	
	RandomStream = FRandomStream(Seed);
	LOG_SUCCESS("Seed set to: %i", Seed);
}

int AAberrationGameState::GetSeed()
{
	if (Seed < 0)
	{
		GenerateSeed();
	}
	
	return Seed;
}

FRandomStream AAberrationGameState::GetRandomStream()
{
	return RandomStream;
}

void AAberrationGameState::RegisterScoreEntry(float Percentage)
{
	LOG("New score entry registered: %f", Percentage);
	Percentages.Add(Percentage);
}
