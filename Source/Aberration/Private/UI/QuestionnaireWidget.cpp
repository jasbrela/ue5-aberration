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
#include "Components/UniformGridPanel.h"

UQuestionnaireWidget::UQuestionnaireWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UQuestionnaireWidget::NativeConstruct()
{
	Confirm->SetOnClick(FOnClickButtonDelegate::CreateUObject(this, &UQuestionnaireWidget::NextPage));
	Option1->SetOnClickQuestion(FOnClickQuestionButtonDelegate::CreateUObject(this, &UQuestionnaireWidget::OnClickOption));
	Option2->SetOnClickQuestion(FOnClickQuestionButtonDelegate::CreateUObject(this, &UQuestionnaireWidget::OnClickOption));
	Option3->SetOnClickQuestion(FOnClickQuestionButtonDelegate::CreateUObject(this, &UQuestionnaireWidget::OnClickOption));
	
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

void UQuestionnaireWidget::OnClickOption(const int ID, const bool bIsPressed) const
{
	if (!bHasMultipleAnswers && bIsPressed)
	{
		for (int i = 0; i < Buttons.Num(); i++)
		{
			if (ID == i) continue;
			
			if (Buttons[i]->IsPressed())
			{
				Buttons[i]->Reset(); 
			}
		}
		ToggleConfirmButton(bIsPressed);
	} else
	{
		const bool AnySelected = Buttons.ContainsByPredicate([](const UQuestionButton* Button) { return Button->IsPressed(); });
		ToggleConfirmButton(AnySelected);
	}
}

void UQuestionnaireWidget::ToggleConfirmButton(const bool bEnable) const
{
	Confirm->SetIsEnabled(bEnable);
	Confirm->SetRenderOpacity(bEnable ? 1.0 : 0.2);
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

void UQuestionnaireWidget::IncreaseQuestionNumber()
{
	QuestionNumber++;

	QuestionNumberText->SetText(FText::AsNumber(QuestionNumber));
	QuestionNumberText->SetText(FText::FromString(FString::Printf(TEXT("%i out of %i"), QuestionNumber, MaxQuestions)));
}

void UQuestionnaireWidget::SetAnswerText(const int Index, const FString& Text)
{
	if (Index == 2)
	{
		Buttons[Index]->SetVisibility(Text.IsEmpty() ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	}
	Buttons[Index]->SetText(Text);
	Buttons[Index]->Reset();
}

void UQuestionnaireWidget::SetAnswerStatus(int Index, bool bIsCorrect)
{
	if (bIsCorrect)
	{
		Buttons[Index]->SetIsCorrect(bIsCorrect);
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

void UQuestionnaireWidget::SetOnSubmitQuestion(const FOnSubmitYesNoQuestionDelegate& Callback)
{
	OnSubmitYesNoQuestion = Callback;
}

void UQuestionnaireWidget::ShowResults()
{
	bShowedResults = true;
	
	if (State)
	{
		Confirm->SetText(State->GetPassed() ? TEXT("OK") : TEXT("Retry"));
		State->SaveGame();
	}
	
	WidgetComponent->RequestRedraw();
}

void UQuestionnaireWidget::Inject(AAberrationManager* Manager)
{
	AberrationManager = Manager;
	MaxQuestions = AberrationManager->GetNumberOfCoaches();
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
	
	if (bCanFinishQuestion || Buttons[1]->IsPressed())
	{
		ConfirmReport();
		return;
	}
	
	if (OnSubmitYesNoQuestion.IsBound())
    {
    	OnSubmitYesNoQuestion.Execute();
    }
	
	WidgetComponent->RequestRedraw();
}

