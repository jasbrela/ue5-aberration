// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/ButtonStyleData.h"
#include "TerminalButton.generated.h"

DECLARE_DELEGATE(FOnClickButtonDelegate)

/**
 * 
 */
UCLASS()
class ABERRATION_API UTerminalButton : public UUserWidget
{
	GENERATED_BODY()
public:
	UTerminalButton(const FObjectInitializer& ObjectInitializer);
	virtual void Reset();
	virtual void UpdateButtonStyle() const;
	void SetOnClick(const FOnClickButtonDelegate& Callback);
	void SetText(const FString& NewText) const;
	bool IsPressed() const;
	
protected:
	UFUNCTION()
	virtual void OnClickButton();
	
	UPROPERTY()
	bool bIsPressed = false;
	
	FOnClickButtonDelegate OnClick;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text;
	
	UPROPERTY(EditAnywhere)
	bool bStayPressed = false;
private:
	UPROPERTY(meta = (BindWidget))
	UButton* Button;

	/** This value is only used when bStayPressed is true */
	UPROPERTY(EditDefaultsOnly)
	UButtonStyleData* DefaultStyle;
	/** This value is only used when bStayPressed is true */
	UPROPERTY(EditDefaultsOnly)
	UButtonStyleData* PressedStyle;
	
};
