// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
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
class ABERRATION_API UMenuWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UMenuWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	void SetCharacter(AAberrationCharacter* Character);
	void SetGameState(AAberrationGameState* State);

private:
	bool bCanSave = false;
	
	UFUNCTION(BlueprintCallable)
	void OnClickQuitButton();

	UFUNCTION(BlueprintCallable)
	void OnClickResumeButton();

	UPROPERTY()
	AAberrationCharacter* AberrationCharacter;
	UPROPERTY()
	AAberrationGameState* AberrationState;
};
