// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalWidget.h"

#include "AberrationGameState.h"
#include "AberrationManager.h"
#include "FTerminalButtonData.h"
#include "Terminal.h"
#include "DebugMacros.h"
#include "FAnswerData.h"
#include "Helper.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

UTerminalWidget::UTerminalWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UTerminalWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Option1->OnClicked.AddDynamic(this, &UTerminalWidget::OnClickOption1);
	Option2->OnClicked.AddDynamic(this, &UTerminalWidget::OnClickOption2);
	Option3->OnClicked.AddDynamic(this, &UTerminalWidget::OnClickOption3);
	Confirm->OnClicked.AddDynamic(this, &UTerminalWidget::NextPage);
	
	Buttons.Add(FTerminalButtonData(Option1, Option1Text));
	Buttons.Add(FTerminalButtonData(Option2, Option2Text));
	Buttons.Add(FTerminalButtonData(Option3, Option3Text));

	Background->SetBrushFromTexture(AttentionTexture, true);

	State = GetWorld()->GetGameState<AAberrationGameState>();
	SeedText->SetText(FText::FromString(FString::Printf(TEXT("OS-%i"), State->GetSeed())));
}

void UTerminalWidget::ShowReport()
{
	ResetButtonIsCorrect();
	ResetButtonsSelectedState();
	
	GenerateYesNoQuestion();

	QuestionsCanvas->SetVisibility(ESlateVisibility::Visible);
	Background->SetBrushFromTexture(QuestionTexture, true);
	Confirm->SetVisibility(ESlateVisibility::Collapsed);	
}

void UTerminalWidget::Inject(ATerminal* TerminalParent)
{
	Terminal = TerminalParent;
}

void UTerminalWidget::Inject(AAberrationManager* Manager)
{
	AberrationManager = Manager;
}

void UTerminalWidget::Inject(UWidgetComponent* Component)
{
	ThisComponent = Component;
}

void UTerminalWidget::ResetButtonIsCorrect()
{
	for (int i = 0; i < Buttons.Num(); i++)
	{
		if (Buttons[i].bIsCorrect)
		{
			Buttons[i].bIsCorrect = false;
			UpdateButtonStyle(i);
		}
	}
}

void UTerminalWidget::SetButtonIsCorrect(int Option, bool IsCorrect) { Buttons[Option-1].bIsCorrect = IsCorrect; }
void UTerminalWidget::SetButtonText(int Option, FString Text) { Buttons[Option-1].SetText(Text); }
void UTerminalWidget::SetButtonVisibility(int Option, bool Visible) { Buttons[Option-1].ToggleVisibility(Visible); }

void UTerminalWidget::DisplayAnswers()
{
	for (int i = 0; i < Buttons.Num(); i++)
	{
		const int Option = i + 1;
		SetButtonText(Option, Answers[i].Text);
		SetButtonIsCorrect(Option, Answers[i].bIsCorrect);
	}
	SetButtonVisibility(3, true);

	ThisComponent->RequestRedraw();
}

void UTerminalWidget::OnClickOption1() { OnClickOption(1); }
void UTerminalWidget::OnClickOption2() { OnClickOption(2); }
void UTerminalWidget::OnClickOption3() { OnClickOption(3); }

void UTerminalWidget::OnClickOption(int Option)
{
	const int Index = Option - 1;
	
	if (bMultipleAnswers)
	{
		Buttons[Index].bIsSelected = !Buttons[Index].bIsSelected;
		
		UpdateButtonStyle(Index);
		
		const bool AnySelected = Buttons.ContainsByPredicate([](FTerminalButtonData Button) { return Button.bIsSelected; });

		ToggleConfirmButton(AnySelected);
	}
	else
	{
		if (Buttons[Index].bIsSelected)
		{
			Buttons[Index].bIsSelected = false;
			UpdateButtonStyle(Index);
			ToggleConfirmButton(false);
		}
		else
		{
			ResetButtonsSelectedState();
			
			Buttons[Index].bIsSelected = true;
			UpdateButtonStyle(Index);
			ToggleConfirmButton(true);
		}
	}
}

void UTerminalWidget::NextPage()
{
	if (bFinished)
	{
		UGameplayStatics::OpenLevel(this, TEXT("Train"));
		LOG_SUCCESS("Player finished game");
		return;
	}
	
	if (bCanConfirm || Buttons[1].bIsSelected) {
		ConfirmReport();
		return;
	}

	if (GetWorld())
	{
		ResetButtonsSelectedState();
		GenerateQuestion();
	} else
	{
		ConfirmReport();
		ToggleConfirmButton(false);
		Background->SetBrushFromTexture(FailureTexture, true);
		return;
	}

	bCanConfirm = true;

	ThisComponent->RequestRedraw();
}

void UTerminalWidget::ConfirmReport()
{
	Terminal->ConfirmReport();

	ToggleConfirmButton(false);
	
	QuestionsCanvas->SetVisibility(ESlateVisibility::Hidden);

	if (AberrationManager != nullptr && AberrationManager->WasLastCoach())
	{
		Background->SetBrushFromTexture(LoadingTexture, true);
		GetWorld()->GetTimerManager().SetTimer(LoadingTimerHandle, this, &UTerminalWidget::DisplayScore, 2.f, false);
	}
	else
	{
		Background->SetBrushFromTexture(SuccessTexture, true);
	}
	
	float Score = 0.f;

	if (bMultipleAnswers)
	{
		for (int i = 0; i < Buttons.Num(); i++)
		{
			//LOG("Selected: %s  Correct: %s",  Buttons[i].bIsSelected ? TEXT("true") : TEXT("false"), Buttons[i].bIsCorrect ? TEXT("true") : TEXT("false"));
			if (Buttons[i].bIsSelected == Buttons[i].bIsCorrect)
			{
				Score += 1.f;
			}
		}
		
		//LOG("Score: %f / %i", Score, Buttons.Num());
		
		State->RegisterScoreEntry(Score / Buttons.Num());
	} else
	{
		for (int i = 0; i < Buttons.Num(); i++)
		{
			if (Buttons[i].bIsSelected && Buttons[i].bIsCorrect)
			{
				Score += 1.f;
				break;
			}
		}
		//LOG("Score: %f / 1", Score);
		State->RegisterScoreEntry(Score);
	}
	
	
	for (const FTerminalButtonData ButtonData : Buttons)
	{
		ButtonData.Button->SetStyle(DefaultStyle);
	}
	
	ThisComponent->RequestRedraw();
}

void UTerminalWidget::ToggleConfirmButton(bool Visible) const
{
	Confirm->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UTerminalWidget::ResetButtonsSelectedState()
{
	for (int i = 0; i < Buttons.Num(); i++)
	{
		if (Buttons[i].bIsSelected)
		{
			Buttons[i].bIsSelected = false;
			UpdateButtonStyle(i);
		}
	}
	
	ToggleConfirmButton(false);

	ThisComponent->RequestRedraw();
}

void UTerminalWidget::UpdateButtonStyle(int Index)
{
	if (Buttons[Index].bIsSelected)
	{
		Buttons[Index].Button->SetStyle(PressedStyle);
	} else
	{
		Buttons[Index].Button->SetStyle(DefaultStyle);
	}
}

void UTerminalWidget::GenerateYesNoQuestion()
{
	bMultipleAnswers = false;
	bCanConfirm = false;
	
	Question->SetText(FText::FromString(TEXT("Have you found any aberrations in this train coach?")));

	const TArray<FString> CurrentAberrations = Terminal->GetPreviousActiveAberrationsNames();
	const bool bIsThereAnyAberration = !CurrentAberrations.IsEmpty();
	
	//LOG("Is there any aberration? %s", bIsThereAnyAberration ? TEXT("true") : TEXT("false"));
	
	SetButtonIsCorrect(1, bIsThereAnyAberration);
	SetButtonText(1, TEXT("Yes"));

	SetButtonIsCorrect(2, !bIsThereAnyAberration);
	SetButtonText(2, TEXT("No"));
	
	SetButtonVisibility(3, false);
	
	ThisComponent->RequestRedraw();
}

void UTerminalWidget::GenerateQuestion()
{
	ResetButtonsSelectedState();
	
	if (State)
	{
		Stream = State->GetRandomStream();
		const int QuestionType = Stream.RandRange(0, 2);

		Answers.Empty();
		//LOG("Generated question of type %i", QuestionType);
		
		TArray<FString> OtherAberrations = Terminal->GetPreviousOtherThanActiveAberrationsNames();
		TArray<FString> CurrentAberrations = Terminal->GetPreviousActiveAberrationsNames();
		
		if (QuestionType >= 1) // Which were found
		{
			Question->SetText(FText::FromString(TEXT("Which of these aberrations was present in the coach?")));

			bMultipleAnswers = false;
			for (int i = 0; i < CurrentAberrations.Num(); i++)
			{
				Answers.Add(FAnswerData(CurrentAberrations[i], true));
			}
			
			for (int i = Answers.Num(); i <= Buttons.Num(); i++)
			{
				const FString RandomAberration = OtherAberrations[Stream.RandRange(0, OtherAberrations.Num() - 1)];
				OtherAberrations.Remove(RandomAberration);

				Answers.AddUnique(FAnswerData(RandomAberration, false));
			}
		}
		else // Which were not found
		{
			Question->SetText(FText::FromString(TEXT("Which aberrations were NOT present in the coach?")));
			bMultipleAnswers = true;

			int AberrationsFromThisCoachQuantity = 0;
			
			if (!CurrentAberrations.IsEmpty())
			{
				AberrationsFromThisCoachQuantity = Stream.RandRange(1, FMath::Min(CurrentAberrations.Num()-1, 2));
				CurrentAberrations = ShuffleArray(CurrentAberrations, Stream);
			}

			for (int i = 0; i < Buttons.Num(); i++)
			{
				if (i < AberrationsFromThisCoachQuantity)
				{
					LOG("[A] Added: %s", *CurrentAberrations[i]);
					Answers.Add(FAnswerData(CurrentAberrations[i], false));
				} else
				{
					const int Index = Stream.RandRange(0, OtherAberrations.Num() - 1);
					const FString RandomAberration = OtherAberrations[Index];
					OtherAberrations.RemoveAt(Index);
					LOG("[B] Added: %s", *RandomAberration);
					Answers.Add(FAnswerData(RandomAberration, true));
				}
			}
		}
		
		bCanConfirm = true;
		Answers = ShuffleArray(Answers, Stream);
		DisplayAnswers();
	}
}

void UTerminalWidget::DisplayScore()
{
	bFinished = true;
	if (State)
	{
		if (State->GetPassed())
		{
			Background->SetBrushFromTexture(ResultSuccessTexture, true);
		} else
		{
			Background->SetBrushFromTexture(ResultFailureTexture, true);
		}

		State->SaveGame();
	}

	ConfirmText->SetText(FText::FromString(TEXT("OK")));
	ToggleConfirmButton(true);
	
	ScorePercentageText->SetText(FText::FromString(FString::Printf(TEXT("%i%%"),  State->GetFinalScorePercentage())));
	ScorePercentageText->SetVisibility(ESlateVisibility::Visible);
	OutOfPointsText->SetText(FText::FromString(FString::Printf(TEXT("%.2f out of %i points"),  State->GetFinalScore(), State->GetMaxPoints())));
	OutOfPointsText->SetVisibility(ESlateVisibility::Visible);
	IncorrectAnswersText->SetText(FText::FromString(FString::Printf(TEXT("%i incorrect answers"),  State->GetIncorrectAnswers())));
	IncorrectAnswersText->SetVisibility(ESlateVisibility::Visible);

	ThisComponent->RequestRedraw();
}
