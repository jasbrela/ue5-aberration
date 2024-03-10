// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalWidget.h"

#include "FTerminalButtonData.h"
#include "Terminal.h"
#include "DebugMacros.h"
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

	Buttons.Add(FTerminalButtonData(Option1));
	Buttons.Add(FTerminalButtonData(Option2));
	Buttons.Add(FTerminalButtonData(Option3));
}

void UTerminalWidget::ShowReport()
{
	bMultipleAnswers = false;
	Question->SetText(FText::FromString(TEXT("Have you found any aberrations in this train coach?")));
	Option1Text->SetText(FText::FromString(TEXT("Yes")));
	Option2Text->SetText(FText::FromString(TEXT("No")));
	Option3->SetVisibility(ESlateVisibility::Collapsed);
	
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

void UTerminalWidget::SetCorrectAnswer(int Option, bool IsCorrect)
{
	Buttons[Option-1].bIsCorrect = IsCorrect;
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
	ResetOptionsState();
	
	if (bCanConfirm) {
		ConfirmReport();
		return;
	}

	if (Buttons[1].bIsSelected)
	{
		ConfirmReport();
		return;
	}
	
	Question->SetText(FText::FromString(TEXT("Question")));
	Option1Text->SetText(FText::FromString(TEXT("A")));
	Option2Text->SetText(FText::FromString(TEXT("B")));	
	Option3Text->SetText(FText::FromString(TEXT("C")));
	Option3->SetVisibility(ESlateVisibility::Visible);
	bCanConfirm = true;
	
	// depend on the question
	bMultipleAnswers = true;
}

void UTerminalWidget::ConfirmReport()
{
	Terminal->ConfirmReport();
	
	QuestionsCanvas->SetVisibility(ESlateVisibility::Hidden);
	Background->SetBrushFromTexture(SuccessTexture, true);

	for (FTerminalButtonData ButtonData : Buttons)
	{
		ButtonData.Button->SetStyle(DefaultStyle);
	}
}

void UTerminalWidget::ToggleConfirmButton(bool Visible)
{
	Confirm->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UTerminalWidget::ResetOptionsState()
{
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
	const TArray<FString> Names = Terminal->GetActiveAberrationsNames();
	const bool CoachContainsAberration = Names.Num() > 0;
}
