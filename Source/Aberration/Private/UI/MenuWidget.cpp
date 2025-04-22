// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/MenuWidget.h"

#include "AberrationCharacter.h"
#include "AberrationGameState.h"
#include "AberrationSaveGame.h"
#include "InputActionValue.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Helper.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "UI/SettingsViewModel.h"

UMenuWidget::UMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMenuWidget::OnClickQuitButton()
{
	FGenericPlatformMisc::RequestExit(false);
}

void UMenuWidget::OnClickResumeButton()
{
	if (AberrationCharacter == nullptr) return;

	SaveSettings();
	
	AberrationCharacter->Pause(FInputActionValue(true));
}

void UMenuWidget::SetCharacter(AAberrationCharacter* Character)
{
	AberrationCharacter = Character;
}

void UMenuWidget::SetGameState(AAberrationGameState* State)
{
	AberrationState = State;
	AberrationState->LoadGame();	
	bCanSave = true;
}

void UMenuWidget::SaveSettings() const
{
	if (bCanSave && AberrationState)
	{
		AberrationState->SaveSettings();
	}

}
