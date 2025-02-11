// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TerminalWidget.generated.h"

class UTerminalButton;
class UWidgetComponent;
class AAberrationManager;
class AAberrationGameState;
struct FAnswerData;
struct FActiveAberrations;
struct FTerminalButtonData;
class ATerminal;
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
	void Inject(AAberrationManager* Manager);
	void Inject(UWidgetComponent* Component);

private:
	void ResetButtonIsCorrect();
	void SetButtonIsCorrect(int Option, bool IsCorrect);
	void SetButtonText(int Option, FString Text);
	void SetButtonVisibility(int Option, bool Visible);
	void DisplayAnswers();
	void OnClickOption(int Option);
	void ConfirmReport();
	void ToggleConfirmButton(bool Enable) const;
	void ResetButtonsSelectedState();
	void UpdateButtonStyle(int Index);
	void GenerateYesNoQuestion();
	void GenerateQuestion();
	void DisplayScore();
	bool bMultipleAnswers = false;
	bool bCanConfirm = false;
	bool bFinished = false;
	
	FRandomStream Stream;
	TArray<FTerminalButtonData> Buttons;
	TArray<FAnswerData> Answers;
	
	UFUNCTION()
	void OnClickOption1();
	
	UFUNCTION()
	void OnClickOption2();
	
	UFUNCTION()
	void OnClickOption3();

	UFUNCTION()
	void NextPage();
	
	UPROPERTY()
	AAberrationGameState* State;

	UPROPERTY()
	UWidgetComponent* ThisComponent;

	UPROPERTY()
	ATerminal* Terminal;

	UPROPERTY()
	AAberrationManager* AberrationManager;

	FTimerHandle LoadingTimerHandle;
	
	UPROPERTY(EditDefaultsOnly)
	FButtonStyle DefaultStyle;
	UPROPERTY(EditDefaultsOnly)
	FButtonStyle PressedStyle;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Background;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* QuestionsCanvas;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* FailureTexture;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* AttentionTexture;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* QuestionTexture;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* SuccessTexture;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* LoadingTexture;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* ResultSuccessTexture;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* ResultFailureTexture;


	UPROPERTY(meta = (BindWidget))
	UTerminalButton* OptionButton1;
	UPROPERTY(meta = (BindWidget))
	UTerminalButton* OptionButton2;
	UPROPERTY(meta = (BindWidget))
	UTerminalButton* OptionButton3;
	
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
	UTextBlock* ScorePercentageText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* OutOfPointsText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* IncorrectAnswersText;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Confirm;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ConfirmText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SeedText;
};
