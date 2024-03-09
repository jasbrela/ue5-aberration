// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TerminalWidget.generated.h"

class ATerminal;
class UCheckBox;
class UCanvasPanel;
class UImage;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class ABERRATION_API UTerminalWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UTerminalWidget(const FObjectInitializer& ObjectInitializer);
    virtual void NativeConstruct() override;
	void ShowReport();
	void Inject(ATerminal* TerminalParent);

private:
	void OnClickOption(int Option);
	void ConfirmReport();
	void ToggleConfirmButton(bool Visible);
	void ResetOptionsState();
	void UpdateButtonStyle(int Index);
	bool bMultipleAnswers = false;
	bool bCanConfirm = false;
	
	UFUNCTION()
	void OnClickOption1();
	
	UFUNCTION()
	void OnClickOption2();
	
	UFUNCTION()
	void OnClickOption3();

	UFUNCTION()
	void NextPage();

	UPROPERTY()
	ATerminal* Terminal;
	TArray<UButton*> ButtonOptions;
	TArray<bool> ButtonStates;

	UPROPERTY(EditDefaultsOnly)
	FButtonStyle DefaultStyle;
	UPROPERTY(EditDefaultsOnly)
	FButtonStyle PressedStyle;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Background;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* QuestionsCanvas;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* SuccessTexture;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* QuestionTexture;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestionNumber;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Question;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Option1Text;
	UPROPERTY(meta = (BindWidget))
	UButton* Option1;
	
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Option2Text;
	UPROPERTY(meta = (BindWidget))
	UButton* Option2;

	
	UPROPERTY(meta = (BindWidget))
	UButton* Option3;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Option3Text;

	
	UPROPERTY(meta = (BindWidget))
	UButton* Confirm;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ConfirmText;
};
