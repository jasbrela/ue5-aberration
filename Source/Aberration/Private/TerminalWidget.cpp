// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalWidget.h"

#include "AberrationGameState.h"
#include "FTerminalButtonData.h"
#include "Terminal.h"
#include "DebugMacros.h"
#include "FAnswerData.h"
#include "Helper.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

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
}

void UTerminalWidget::ShowReport()
{
	bMultipleAnswers = false;
	bCanConfirm = false;
	Question->SetText(FText::FromString(TEXT("Have you found any aberrations in this train coach?")));
	Buttons[0].SetText(TEXT("Yes"));
	Buttons[1].SetText(TEXT("No"));
	Buttons[2].ToggleVisibility(false);
	
	QuestionsCanvas->SetVisibility(ESlateVisibility::Visible);
	Background->SetBrushFromTexture(QuestionTexture, true);
	Confirm->SetVisibility(ESlateVisibility::Collapsed);
}

void UTerminalWidget::Inject(ATerminal* TerminalParent)
{
	Terminal = TerminalParent;
}

void UTerminalWidget::ResetCorrectAnswers()
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

void UTerminalWidget::SetButtonIsCorrect(int Option, bool IsCorrect)
{
	Buttons[Option-1].bIsCorrect = IsCorrect;
}

void UTerminalWidget::SetButtonText(int Option, FString Text)
{
	Buttons[Option-1].SetText(Text);
}

void UTerminalWidget::DisplayAnswers()
{
	for (int i = 0; i < Buttons.Num(); i++)
	{
		const int Option = i + 1;
		SetButtonText(Option, Answers[i].Text);
		SetButtonIsCorrect(Option, Answers[i].bIsCorrect);
	}
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
			ResetOptionsState();
			
			Buttons[Index].bIsSelected = true;
			UpdateButtonStyle(Index);
			ToggleConfirmButton(true);
		}
	}
}

void UTerminalWidget::NextPage()
{
	if (bCanConfirm) {
		ConfirmReport();
		return;
	}

	if (Buttons[1].bIsSelected)
	{
		ConfirmReport();
		return;
	}

	if (GetWorld())
	{
		ResetOptionsState();
		GenerateQuestion();
	} else
	{
		// TODO: Display failed screen
		ConfirmReport();
		Background->SetBrushFromTexture(FailureTexture, true);
		return;
	}
	
	Buttons[2].ToggleVisibility(true);
	bCanConfirm = true;
	
	// depend on the question
	bMultipleAnswers = true;
}

void UTerminalWidget::ConfirmReport()
{
	Terminal->ConfirmReport();
	
	QuestionsCanvas->SetVisibility(ESlateVisibility::Hidden);
	Background->SetBrushFromTexture(SuccessTexture, true);
	
	float Score = 0.f;
	for (int i = 0; i < Buttons.Num(); i++)
	{
		LOG("Selected: %s  Correct: %s",  Buttons[i].bIsSelected ? TEXT("true") : TEXT("false"), Buttons[i].bIsCorrect ? TEXT("true") : TEXT("false"));
		if (Buttons[i].bIsSelected == Buttons[i].bIsCorrect)
		{
			Score += 1.f;
		}
	}
	
	State->RegisterScoreEntry(Score / Buttons.Num());
	
	for (FTerminalButtonData ButtonData : Buttons)
	{
		ButtonData.Button->SetStyle(DefaultStyle);
	}
}

void UTerminalWidget::ToggleConfirmButton(bool Visible) const
{
	Confirm->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UTerminalWidget::ResetOptionsState()
{
	LOG("ResetOptionsState");
	for (int i = 0; i < Buttons.Num(); i++)
	{
		if (Buttons[i].bIsSelected)
		{
			Buttons[i].bIsSelected = false;
			UpdateButtonStyle(i);
		}
	}
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

void UTerminalWidget::GenerateQuestion()
{
	if (State == nullptr)
	{
		State = GetWorld()->GetGameState<AAberrationGameState>();
	}
	
	if (State)
	{
		Stream = State->GetRandomStream();
		const int QuestionType = Stream.RandRange(0, 1);

		//LOG("Generated question of type %i", QuestionType);
		
		TArray<FString> OtherAberrations = Terminal->GetOtherThanActiveAberrationsNames();
		TArray<FString> CurrentAberrations = Terminal->GetActiveAberrationsNames();
		
		if (QuestionType == 0) // Which were found
		{
			Question->SetText(FText::FromString(TEXT("Which aberrations were present in the carriage?")));

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
		else if (QuestionType == 1) // Which were not found
		{
			Question->SetText(FText::FromString(TEXT("Which aberrations were not present in the carriage?")));

			int AberrationsFromThisCoachQuantity = 0;
			
			if (CurrentAberrations.Num() > 0)
			{
				AberrationsFromThisCoachQuantity = Stream.RandRange(0, FMath::Min(CurrentAberrations.Num()-1, 2));
				CurrentAberrations = ShuffleArray(CurrentAberrations, Stream);
			}

			for (int i = 0; i < Buttons.Num(); i++)
			{
				if (i < AberrationsFromThisCoachQuantity)
				{
					Answers.Add(FAnswerData(CurrentAberrations[i], false));
				} else
				{
					const FString RandomAberration = OtherAberrations[Stream.RandRange(0, OtherAberrations.Num() - 1)];
					OtherAberrations.Remove(RandomAberration);
					
					Answers.Add(FAnswerData(RandomAberration, true));
				}
			}
		}
		
		Answers = ShuffleArray(Answers, Stream);
		DisplayAnswers();
	}
}
