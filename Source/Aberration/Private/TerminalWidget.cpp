// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalWidget.h"

#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"

UTerminalWidget::UTerminalWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UTerminalWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Option1->OnClicked.AddDynamic(this, &UTerminalWidget::OnClickOption1);
	Option2->OnClicked.AddDynamic(this, &UTerminalWidget::OnClickOption2);
	Option3->OnClicked.AddDynamic(this, &UTerminalWidget::OnClickOption3);
	Confirm->OnClicked.AddDynamic(this, &UTerminalWidget::HideReport);

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
	QuestionsCanvas->SetVisibility(ESlateVisibility::Visible);
	Background->SetBrushFromTexture(QuestionTexture, true);
	Confirm->SetVisibility(ESlateVisibility::Collapsed);
}

void UTerminalWidget::OnClickOption1() { OnClickOption(1); }
void UTerminalWidget::OnClickOption2() { OnClickOption(2); }
void UTerminalWidget::OnClickOption3() { OnClickOption(3); }

void UTerminalWidget::OnClickOption(int Option)
{
	ButtonStates[Option-1] = !ButtonStates[Option-1];
	
	if (ButtonStates[Option-1])
	{
		ButtonOptions[Option-1]->SetStyle(PressedStyle);
	} else
	{
		ButtonOptions[Option-1]->SetStyle(DefaultStyle);
	}

	const bool AnySelected = ButtonStates.Contains(true);

	Confirm->SetVisibility(AnySelected ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UTerminalWidget::HideReport()
{
	QuestionsCanvas->SetVisibility(ESlateVisibility::Hidden);
	Background->SetBrushFromTexture(SuccessTexture, true);

	for (UButton* Button : ButtonOptions)
	{
		Button->SetStyle(DefaultStyle);
	}
}
