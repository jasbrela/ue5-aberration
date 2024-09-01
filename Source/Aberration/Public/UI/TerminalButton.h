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
	virtual void NativeConstruct() override;

	bool IsPressed() const;
	void UpdateButtonStyle() const;
	virtual void Reset();
	void SetOnClick(const FOnClickButtonDelegate& Callback);
	void SetText(const FString& NewText) const;
	UPROPERTY(meta = (BindWidget))
	UButton* Button;


	UPROPERTY(EditAnywhere)
	int ID = -1;
	
protected:
	UPROPERTY()
	bool bIsPressed = false;
	
private:
	UFUNCTION()
	void OnClickButton();
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text;
	
	UPROPERTY(EditDefaultsOnly, meta=(EditCondition = "bStayPressed"), Category="Style")
	UButtonStyleData* DefaultStyle;
	UPROPERTY(EditDefaultsOnly, meta=(EditCondition = "bStayPressed"), Category="Style")
	UButtonStyleData* PressedStyle;
	
	UPROPERTY(EditDefaultsOnly)
	bool bStayPressed = false;

	FOnClickButtonDelegate OnClick;
	
	
};
