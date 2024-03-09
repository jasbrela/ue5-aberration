// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalWidget.h"

#include "Terminal.h"
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

	// todo: create struct for this
	ButtonOptions.Add(Option1);
	ButtonOptions.Add(Option2);
	ButtonOptions.Add(Option3);

	ButtonStates.Add(false);
	ButtonStates.Add(false);
	ButtonStates.Add(false);

	DefaultStyle = ButtonOptions[0]->GetStyle();
	
	PressedStyle = ButtonOptions[0]->GetStyle();
	PressedStyle.Normal = DefaultStyle.Pressed;
	PressedStyle.Hovered = DefaultStyle.Pressed;
}

void UTerminalWidget::ShowReport()
{
	bMultipleChoices = false;
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

void UTerminalWidget::OnClickOption1() { OnClickOption(1); }
void UTerminalWidget::OnClickOption2() { OnClickOption(2); }
void UTerminalWidget::OnClickOption3() { OnClickOption(3); }

void UTerminalWidget::OnClickOption(int Option)
{
	const int Index = Option - 1;
	
	if (bMultipleChoices)
	{
		ButtonStates[Index] = !ButtonStates[Index];
		
		UpdateButtonStyle(Index);
		
		const bool AnySelected = ButtonStates.Contains(true);

		ToggleConfirmButton(AnySelected);
	}
	else
	{
		if (ButtonStates[Index]) // SELECTED
		{
			ButtonStates[Index] = false;
			UpdateButtonStyle(Option);
			ToggleConfirmButton(false);
		}
		else
		{
			ResetOptionsState();
			
			ButtonStates[Index] = true;
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

	if (ButtonStates[1])
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
	bMultipleChoices = true;
}

void UTerminalWidget::ConfirmReport()
{
	Terminal->ConfirmReport();
	
	QuestionsCanvas->SetVisibility(ESlateVisibility::Hidden);
	Background->SetBrushFromTexture(SuccessTexture, true);

	for (UButton* Button : ButtonOptions)
	{
		Button->SetStyle(DefaultStyle);
	}
}

void UTerminalWidget::ToggleConfirmButton(bool Visible)
{
	Confirm->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UTerminalWidget::ResetOptionsState()
{
	for (int i = 0; i < ButtonStates.Num(); i++)
	{
		if (ButtonStates[i])
		{
			ButtonStates[i] = false;
			UpdateButtonStyle(i);
		}
	}
}

void UTerminalWidget::UpdateButtonStyle(int Index)
{
	if (ButtonStates[Index])
	{
		ButtonOptions[Index]->SetStyle(PressedStyle);
	} else
	{
		ButtonOptions[Index]->SetStyle(DefaultStyle);
	}
}
