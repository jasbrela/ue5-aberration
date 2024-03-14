// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "AberrationCharacter.h"
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

void UMenuWidget::OnVolumeChanged(float value)
{
	VolumeValue->SetText(Convert(value));
	UGameplayStatics::SetSoundMixClassOverride(this, SoundClassMix, SoundClass, FMath::Clamp(value, 0, 1));
}

void UMenuWidget::OnSensXChanged(float value)
{
	if (AberrationCharacter)
	{
		AberrationCharacter->SetSensX(value);
		SensXValue->SetText(Convert(value));
	}
}

void UMenuWidget::OnSensYChanged(float value)
{
	if (AberrationCharacter)
	{
		AberrationCharacter->SetSensY(value);
		SensYValue->SetText(Convert(value));
	}
}

void UMenuWidget::Inject(AAberrationCharacter* Character)
{
	AberrationCharacter = Character;
}
