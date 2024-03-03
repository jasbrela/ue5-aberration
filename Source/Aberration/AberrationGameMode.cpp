// Copyright Epic Games, Inc. All Rights Reserved.

#include "AberrationGameMode.h"
#include "AberrationCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAberrationGameMode::AAberrationGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
