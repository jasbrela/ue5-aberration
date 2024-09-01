// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestionnaireWidget.generated.h"

class AAberrationManager;
class UTerminalButton;
class UQuestionButton;
class UImage;
class UCanvasPanel;
class AAberrationGameState;
class UTextBlock;
class ATerminal;
class UWidgetComponent;

DECLARE_DELEGATE(FOnSubmitQuestionDelegate)

/**
 * 
 */
UCLASS()
class ABERRATION_API UQuestionnaireWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuestionnaireWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	void Open() const;
	void Close() const;
	
	void ResetButtons() const;
	
	void SetAnswerText(int Index, const FString& Text);
	void SetAnswerStatus(int Index, bool bIsWrong);
	void SetMultipleAnswers(bool bValue);
	void SetCanFinishQuestion(bool bValue);
	void SetQuestionTitle(const FString& Text) const;
	void SetOnSubmitQuestion(const FOnSubmitQuestionDelegate& Callback);

	void ShowResults();

	void Inject(AAberrationManager* Manager);
	void Inject(UWidgetComponent* Component);
	void Inject(ATerminal* TerminalParent);

private:
	void ToggleConfirmButton(bool Enable) const;
	void ConfirmReport();
	void OnClickOption() const;
	bool bShowedResults = false;
	bool bHasMultipleAnswers = false;
	bool bCanFinishQuestion = false;
	int QuestionNumber = 1;
	FOnSubmitQuestionDelegate OnSubmitQuestion;
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
	UCanvasPanel* WrapCanvas;
	
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
	
	UFUNCTION()
	void NextPage();
};
