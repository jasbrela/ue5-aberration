// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/ButtonStyleData.h"
#include "TerminalButton.generated.h"

DECLARE_DELEGATE(FOnClickTerminalButton)

/**
 * 
 */
UCLASS()
class ABERRATION_API UTerminalButton : public UUserWidget
{
	GENERATED_BODY()
public:
	UTerminalButton(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	bool GetIsPressed() const;
	void UpdateButtonStyle(bool bPress);
	void SetOnClick(FOnClickTerminalButton& Callback);
	void SetText(const FString& NewText) const;
	UPROPERTY(meta = (BindWidget))
	UButton* Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text;

	UPROPERTY()
	bool bIsPressed = false;
	
private:
	UFUNCTION()
	void OnClickButton();
	
	UPROPERTY(EditDefaultsOnly, meta=(EditCondition = "bStayPressed"))
	UButtonStyleData* DefaultStyle;
	UPROPERTY(EditDefaultsOnly, meta=(EditCondition = "bStayPressed"))
	UButtonStyleData* PressedStyle;

	UPROPERTY(EditDefaultsOnly)
	bool bStayPressed = false;

	FOnClickTerminalButton OnClick;
	
	
};
