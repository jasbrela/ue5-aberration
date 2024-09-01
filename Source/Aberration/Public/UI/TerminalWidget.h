// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuestionButton.h"
#include "Blueprint/UserWidget.h"
#include "TerminalWidget.generated.h"

class AAberrationManager;
class UQuestionnaireWidget;
class UTerminalButton;
class UWidgetComponent;
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
	
	void InitializeTerminal();
	void ShowReport();
	
	void Inject(UWidgetComponent* Component);
	void Inject(AAberrationManager* Manager);
	void Inject(ATerminal* TerminalParent);
private:
	void SetAnswersText();
	void GenerateYesNoQuestion();
	void GenerateQuestion();
	bool bFinished = false;
	
	FRandomStream Stream;
	TArray<FAnswerData> Answers;

	UPROPERTY()
	AAberrationGameState* State;
	UPROPERTY()
	ATerminal* Terminal;
	UPROPERTY()
	UWidgetComponent* WidgetComponent;
	UPROPERTY()
	AAberrationManager* AberrationManager;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Background;

	UPROPERTY(meta = (BindWidget))
	UQuestionnaireWidget* Questionnaire;

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
	UTextBlock* SeedText;
};
