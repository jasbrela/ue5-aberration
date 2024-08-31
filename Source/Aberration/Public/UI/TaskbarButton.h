// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "TaskbarButton.generated.h"

class UWidgetComponent;

class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class ABERRATION_API UTaskbarButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UTaskbarButton(const FObjectInitializer& ObjectInitializer);
	bool GetIsPressed();
	void UpdateButtonStyle(bool bPress);
	
private:	
	UPROPERTY(EditDefaultsOnly, meta=(EditCondition = "bStayPressed"))
	FButtonStyle DefaultStyle;
	UPROPERTY(EditDefaultsOnly, meta=(EditCondition = "bStayPressed"))
	FButtonStyle PressedStyle;
	
	UPROPERTY(meta = (BindWidget))
	UImage* WindowIcon;

	UPROPERTY(meta = (BindWidget))
	UButton* Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text;
	
	UPROPERTY(EditDefaultsOnly)
	bool bStayPressed = false;

	UPROPERTY()
	bool bIsPressed = false;
};
