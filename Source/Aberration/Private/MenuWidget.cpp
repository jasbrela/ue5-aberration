// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "AberrationCharacter.h"
#include "AberrationGameState.h"
#include "AberrationSaveGame.h"
#include "DebugMacros.h"
#include "InputActionValue.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Helper.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

UMenuWidget::UMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	VolumeSlider->OnValueChanged.AddDynamic(this, &UMenuWidget::OnVolumeChanged);
	SensXSlider->OnValueChanged.AddDynamic(this, &UMenuWidget::OnSensXChanged);
	SensYSlider->OnValueChanged.AddDynamic(this, &UMenuWidget::OnSensYChanged);

	QuitButton->OnClicked.AddDynamic(this, &UMenuWidget::OnClickQuitButton);
	ResumeButton->OnClicked.AddDynamic(this, &UMenuWidget::OnClickResumeButton);
}

void UMenuWidget::OnClickQuitButton()
{
	FGenericPlatformMisc::RequestExit(false);
}

void UMenuWidget::OnClickResumeButton()
{
	if (AberrationCharacter)
	{
		AberrationCharacter->Pause(FInputActionValue(true));
	}
}

void UMenuWidget::OnVolumeChanged(float Value)
{
	if (bCanSave && AberrationState)
	{
		AberrationState->SaveVolume(Value);
	}
	
	VolumeSlider->SetValue(Value);
	VolumeValue->SetText(Convert(Value));
	UGameplayStatics::SetSoundMixClassOverride(this, SoundClassMix, SoundClass, FMath::Clamp(Value, 0, 1));
}

void UMenuWidget::OnSensXChanged(float Value)
{
	if (AberrationCharacter)
	{
		if (bCanSave && AberrationState)
		{
			AberrationState->SaveSensX(Value);
		}
		
		AberrationCharacter->SetSensX(Value);
		SensXSlider->SetValue(Value);
		SensXValue->SetText(Convert(Value));
	}
}

void UMenuWidget::OnSensYChanged(float Value)
{
	if (AberrationCharacter)
	{
		if (bCanSave && AberrationState)
		{
			AberrationState->SaveSensY(Value);
		}
		
		AberrationCharacter->SetSensY(Value);
		SensYSlider->SetValue(Value);
		SensYValue->SetText(Convert(Value));
	}
}

void UMenuWidget::Inject(AAberrationCharacter* Character)
{
	AberrationCharacter = Character;
}

void UMenuWidget::Inject(AAberrationGameState* State)
{
	AberrationState = State;

	if (const UAberrationSaveGame* Save = AberrationState->LoadGame())
	{
		OnSensXChanged(Save->SensX);
		OnSensYChanged(Save->SensY);
		OnVolumeChanged(Save->Volume);
	}
	
	bCanSave = true;
}
