// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class AAberrationGameState;
class AAberrationCharacter;
class USlider;
class UButton;
class UCanvasPanel;
class UTextBlock;
/**
 * 
 */
UCLASS()
class ABERRATION_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMenuWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	void Inject(AAberrationCharacter* Character);
	void Inject(AAberrationGameState* State);

private:
	bool bCanSave = false;
	
	UFUNCTION()
	void OnClickQuitButton();

	UFUNCTION()
	void OnClickResumeButton();
	
	UFUNCTION()
	void OnVolumeChanged(float Value);

	UFUNCTION()
	void OnSensXChanged(float Value);

	UFUNCTION()
	void OnSensYChanged(float Value);

	UPROPERTY()
	AAberrationCharacter* AberrationCharacter;
	UPROPERTY()
	AAberrationGameState* AberrationState;
		
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	
	UPROPERTY(meta = (BindWidget))
	USlider* SensYSlider;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SensYValue;
	
	UPROPERTY(meta = (BindWidget))
	USlider* SensXSlider;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SensXValue;
	
	UPROPERTY(meta = (BindWidget))
	USlider* VolumeSlider;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* VolumeValue;

	UPROPERTY(EditDefaultsOnly)
	USoundClass* SoundClass;
	
	UPROPERTY(EditDefaultsOnly)
	USoundMix* SoundClassMix;
};
