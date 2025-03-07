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

/**
 * 
 */
UCLASS()
class ABERRATION_API UQuestionnaireWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuestionnaireWidget(const FObjectInitializer& ObjectInitializer);

	virtual void InitializeWindow();
	void ShowResults();

	void Inject(AAberrationManager* Manager);
	void Inject(UWidgetComponent* Component);
	void Inject(ATerminal* TerminalParent);

private:
	void ConfirmReport();
	bool bShowedResults = false;
	bool bHasMultipleAnswers = false;
	bool bCanFinishQuestion = false;
	int QuestionNumber = 1;
	int MaxQuestions = 10;
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
		
	UFUNCTION()
	void NextPage();
};
