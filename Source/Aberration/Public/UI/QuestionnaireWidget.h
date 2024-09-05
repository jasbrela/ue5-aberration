// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestionnaireWidget.generated.h"

class UButton;
class UUniformGridPanel;
class AAberrationManager;
class UTerminalButton;
class UQuestionButton;
class UImage;
class UCanvasPanel;
class AAberrationGameState;
class UTextBlock;
class ATerminal;
class UWidgetComponent;

DECLARE_DELEGATE(FOnSubmitYesNoQuestionDelegate)

/**
 * 
 */
UCLASS()
class ABERRATION_API UQuestionnaireWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuestionnaireWidget(const FObjectInitializer& ObjectInitializer);

	void InitializeQuestionnaire();

	void Open();
	UFUNCTION()
	void Close();
	
	void ResetButtons() const;

	void IncreaseQuestionNumber();
	void SetAnswerText(int Index, const FString& Text);
	void SetAnswerStatus(int Index, bool bIsCorrect);
	void SetMultipleAnswers(bool bValue);
	void SetCanFinishQuestion(bool bValue);
	void SetQuestionTitle(const FString& Text) const;
	void SetOnSubmitQuestion(const FOnSubmitYesNoQuestionDelegate& Callback);

	void ShowResults();

	void Inject(AAberrationManager* Manager);
	void Inject(UWidgetComponent* Component);
	void Inject(ATerminal* TerminalParent);

private:
	void ToggleConfirmButton(bool bEnable) const;
	void ConfirmReport();
	void OnClickOption(int ID, bool bIsPressed) const;
	bool bShowedResults = false;
	bool bHasMultipleAnswers = false;
	bool bCanFinishQuestion = false;
	int QuestionNumber = 1;
	int MaxQuestions = 10;
	FOnSubmitYesNoQuestionDelegate OnSubmitYesNoQuestion;
	FTimerHandle LoadingTimerHandle;
	TArray<UQuestionButton*> Buttons;

	UPROPERTY()
	AAberrationGameState* State;
	UPROPERTY()
	ATerminal* Terminal;
	UPROPERTY()
	UWidgetComponent* WidgetComponent;
	UPROPERTY()
	AAberrationManager* AberrationManager;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestionText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestionNumberText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxQuestionsNumberText;
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* AnswerFeedback;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Background;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* LoadingTexture;
	
	UPROPERTY(meta = (BindWidget))
	UQuestionButton* Option1;
	UPROPERTY(meta = (BindWidget))
	UQuestionButton* Option2;
	UPROPERTY(meta = (BindWidget))
	UQuestionButton* Option3;
	
	UPROPERTY(meta = (BindWidget))
	UTerminalButton* Confirm;
	
	UPROPERTY(meta = (BindWidget))
	UButton* MinimizeButton;
	
	UFUNCTION()
	void NextPage();
};
