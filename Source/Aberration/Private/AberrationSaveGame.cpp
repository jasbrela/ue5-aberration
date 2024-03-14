// Fill out your copyright notice in the Description page of Project Settings.


#include "AberrationSaveGame.h"

UAberrationSaveGame::UAberrationSaveGame()
{
	Volume = 1.f;
	SensX = 1.f;
	SensY = 1.f;
	ExcludedAberrations.Empty();
	CompletedRuns = 0;
}
