// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/QuestionButton.h"

UQuestionButton::UQuestionButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UQuestionButton::NativeConstruct()
{
	Super::NativeConstruct();
}

void UQuestionButton::SetOnClickQuestion(const FOnClickQuestionButtonDelegate& Callback)
{
	OnClick = Callback;
}

bool UQuestionButton::IsAnswerCorrect() const
{
	return bIsPressed && bIsCorrect;
}

void UQuestionButton::Reset()
{
	Super::Reset();
	bIsCorrect = false;
}

void UQuestionButton::SetIsCorrect(bool IsCorrect)
{
	bIsCorrect = IsCorrect;
}

void UQuestionButton::OnClickButton()
{
	Super::OnClickButton();
	
	if (OnClick.IsBound())
	{
		OnClick.Execute(ID);
	}
}
