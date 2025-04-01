// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/QuestionnaireWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "AberrationGameState.h"
#include "AberrationManager.h"
#include "UI/QuestionButton.h"
#include "Components/Image.h"

UQuestionnaireWidget::UQuestionnaireWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UQuestionnaireWidget::InitializeWindow()
{
	/*Confirm->SetOnClick(FOnClickButtonDelegate::CreateUObject(this, &UQuestionnaireWidget::NextPage));
	Option1->SetOnClickQuestion(FOnClickQuestionButtonDelegate::CreateUObject(this, &UQuestionnaireWidget::OnClickOption));
	Option2->SetOnClickQuestion(FOnClickQuestionButtonDelegate::CreateUObject(this, &UQuestionnaireWidget::OnClickOption));
	Option3->SetOnClickQuestion(FOnClickQuestionButtonDelegate::CreateUObject(this, &UQuestionnaireWidget::OnClickOption));
	
	Buttons.Add(Option1);
	Buttons.Add(Option2);
	Buttons.Add(Option3);
	
	State = GetWorld()->GetGameState<AAberrationGameState>();*/
}

void UQuestionnaireWidget::ConfirmReport()
{
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

void UQuestionnaireWidget::ShowResults()
{
	bShowedResults = true;
	
	if (State)
	{
		Confirm->SetText(State->GetPassed() ? TEXT("OK") : TEXT("Retry"));
		//State->SaveGame();
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
		State->ResetExcludedAberrations();

		UGameplayStatics::OpenLevel(this, TEXT("Train"));
		return;
	}
	
	if (bCanFinishQuestion || Buttons[1]->IsPressed())
	{
		ConfirmReport();
		return;
	}
	
	/*if (OnSubmitYesNoQuestion.IsBound())
    {
    	OnSubmitYesNoQuestion.Execute();
    }*/
	
	WidgetComponent->RequestRedraw();
}

