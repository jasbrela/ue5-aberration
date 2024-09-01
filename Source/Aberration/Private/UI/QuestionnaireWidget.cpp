// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/QuestionnaireWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "AberrationGameState.h"
#include "AberrationManager.h"
#include "UI/QuestionButton.h"
#include "Terminal.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"

UQuestionnaireWidget::UQuestionnaireWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UQuestionnaireWidget::NativeConstruct()
{
	Confirm->SetOnClick(FOnClickButtonDelegate::CreateUObject(this, &UQuestionnaireWidget::NextPage));
	Option1->SetOnClick(FOnClickButtonDelegate::CreateUObject(this, &UQuestionnaireWidget::OnClickOption));
	Option2->SetOnClick(FOnClickButtonDelegate::CreateUObject(this, &UQuestionnaireWidget::OnClickOption));
	Option3->SetOnClick(FOnClickButtonDelegate::CreateUObject(this, &UQuestionnaireWidget::OnClickOption));
	
	Buttons.Add(Option1);
	Buttons.Add(Option2);
	Buttons.Add(Option3);
	
	State = GetWorld()->GetGameState<AAberrationGameState>();
}

void UQuestionnaireWidget::Open() const
{
	WrapCanvas->SetVisibility(ESlateVisibility::Visible);
}

void UQuestionnaireWidget::Close() const
{
	WrapCanvas->SetVisibility(ESlateVisibility::Collapsed);
}

void UQuestionnaireWidget::OnClickOption() const
{
	// TODO: FORCE "RELEASE" OF PREVIOUS SELECTED BUTTONS
	const bool AnySelected = Buttons.ContainsByPredicate([](const UQuestionButton* Button) { return Button->IsPressed(); });
	ToggleConfirmButton(AnySelected);
}

void UQuestionnaireWidget::ToggleConfirmButton(bool Enable) const
{
	Confirm->SetIsEnabled(Enable);
	Confirm->SetRenderOpacity(Enable ? 1.0 : 0.2);
}

void UQuestionnaireWidget::ConfirmReport()
{
	Terminal->ConfirmReport();

	ToggleConfirmButton(false);

	Option1->SetVisibility(ESlateVisibility::Hidden);
	Option2->SetVisibility(ESlateVisibility::Hidden);
	Option3->SetVisibility(ESlateVisibility::Hidden);
	Confirm->SetVisibility(ESlateVisibility::Hidden);

	// TODO: Show popup success
	
	if (AberrationManager != nullptr && AberrationManager->WasLastCoach())
	{
		Background->SetBrushFromTexture(LoadingTexture, true);
		GetWorld()->GetTimerManager().SetTimer(LoadingTimerHandle, this, &UQuestionnaireWidget::ShowResults, 2.f, false);
	}
	
	float Score = 0.f;

	for (int i = 0; i < Buttons.Num(); i++)
	{
		if (Buttons[i]->IsAnswerCorrect())
		{
			Score += 1.f;
			
			if (!bHasMultipleAnswers)
			{
				break;
			}
		}
	}

	float ScoreEntry = Score;
	
	if (bHasMultipleAnswers)
	{
		ScoreEntry /= Buttons.Num();
	}
	
	State->RegisterScoreEntry(ScoreEntry);
		
	WidgetComponent->RequestRedraw();
}

void UQuestionnaireWidget::ResetButtons() const
{
	Option1->Reset();
	Option2->Reset();
	Option3->Reset();

	ToggleConfirmButton(false);
	WidgetComponent->RequestRedraw();
}

void UQuestionnaireWidget::SetAnswerText(const int Index, const FString& Text)
{
	if (Index == 2)
	{
		Buttons[Index]->SetVisibility(Text.IsEmpty() ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	}
	Buttons[Index]->SetText(Text);
}

void UQuestionnaireWidget::SetAnswerStatus(int Index, bool bIsWrong)
{
	if (bIsWrong)
	{
		// TODO: Set text color
	}
}

void UQuestionnaireWidget::SetMultipleAnswers(const bool bValue)
{
	bHasMultipleAnswers = bValue;
}

void UQuestionnaireWidget::SetCanFinishQuestion(bool bValue)
{
	bCanFinishQuestion = bValue;
}

void UQuestionnaireWidget::SetQuestionTitle(const FString& Text) const
{
	QuestionText->SetText(FText::FromString(Text));
}

void UQuestionnaireWidget::SetOnSubmitQuestion(const FOnSubmitQuestionDelegate& Callback)
{
	OnSubmitQuestion = Callback;
}

void UQuestionnaireWidget::ShowResults()
{
	bShowedResults = true;
	
	if (State)
	{
		Confirm->SetText(State->GetPassed() ? TEXT("OK") : TEXT("Retry"));
		State->SaveGame();
	}
	
	/*ScorePercentageText->SetText(FText::FromString(FString::Printf(TEXT("%i%%"),  State->GetFinalScorePercentage())));
	ScorePercentageText->SetVisibility(ESlateVisibility::Visible);
	OutOfPointsText->SetText(FText::FromString(FString::Printf(TEXT("%.2f out of %i points"),  State->GetFinalScore(), State->GetMaxPoints())));
	OutOfPointsText->SetVisibility(ESlateVisibility::Visible);
	IncorrectAnswersText->SetText(FText::FromString(FString::Printf(TEXT("%i incorrect answers"),  State->GetIncorrectAnswers())));
	IncorrectAnswersText->SetVisibility(ESlateVisibility::Visible);*/

	WidgetComponent->RequestRedraw();
}

void UQuestionnaireWidget::Inject(AAberrationManager* Manager)
{
	AberrationManager = Manager;
}

void UQuestionnaireWidget::Inject(UWidgetComponent* Component)
{
	WidgetComponent = Component;
}

void UQuestionnaireWidget::Inject(ATerminal* TerminalParent)
{
	Terminal = TerminalParent;
}

void UQuestionnaireWidget::NextPage()
{
	if (bShowedResults) /* RESTART GAME */
	{
		UGameplayStatics::OpenLevel(this, TEXT("Train"));
		return;
	}
	
	if (bCanFinishQuestion) // TODO: FINISH QUESTION IF (Button[1] (NO) IS SELECTED IN FIRST QUESTION
	{
		ConfirmReport();
		return;
	}
	
	ResetButtons();

	if (OnSubmitQuestion.IsBound())
	{
		OnSubmitQuestion.Execute();
	}

	WidgetComponent->RequestRedraw();
}

