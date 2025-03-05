// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "TerminalWidget.generated.h"

class AAberrationPlayerController;
class UDesktopIcon;
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
class ABERRATION_API UTerminalWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
    UTerminalWidget(const FObjectInitializer& ObjectInitializer);
    virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	/*
	virtual FReply NativeOnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	void InitializeTerminal();
	void ShowReport() const;
	void OnClickAnywhere() const;
	void OnClickDesktopIcon() const;
	void OnClickQuiz() const;
	void OnClickNotes() const;
	
	void Inject(UWidgetComponent* Component);
	void Inject(AAberrationManager* Manager);
	void Inject(ATerminal* TerminalParent);*/
	
private:
	UPROPERTY()
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere)
	USoundCue* MouseClickSound;

	UPROPERTY()
	AAberrationPlayerController* Controller;
	
	/*void SetAnswersText();
	void GenerateYesNoQuestion() const;
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
	UImage* CursorImage;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Background;*/
	
	/*
	UPROPERTY(meta = (BindWidget))
	UQuestionnaireWidget* Questionnaire;
	
	UPROPERTY(meta = (BindWidget))
	UDesktopIcon* QuizIcon;

	UPROPERTY(meta = (BindWidget))
	UDesktopIcon* NotesIcon;*/
	
};
