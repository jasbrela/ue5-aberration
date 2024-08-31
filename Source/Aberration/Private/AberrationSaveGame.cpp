// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "AberrationSaveGame.h"

UAberrationSaveGame::UAberrationSaveGame()
{
	Volume = 1.f;
	SensX = 1.f;
	SensY = 1.f;
	ExcludedAberrations.Empty();
	CompletedRuns = 0;
}
