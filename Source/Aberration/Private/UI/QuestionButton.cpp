// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/QuestionButton.h"

#include "DebugMacros.h"

UQuestionButton::UQuestionButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UQuestionButton::SetOnClickQuestion(const FOnClickQuestionButtonDelegate& Callback)
{
	RegisterButtonCallback();
	
	OnClickQuestion = Callback;
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

void UQuestionButton::SetIsCorrect(const bool bIsQuestionCorrect)
{
	bIsCorrect = bIsQuestionCorrect;
}

void UQuestionButton::OnClickButton()
{
	Super::OnClickButton();
	
	if (OnClickQuestion.IsBound())
	{
		if (ID == -1)
		{
			LOG_WARNING("ID is -1. This might cause unexpected behaviour.");
		}
		OnClickQuestion.Execute(ID, bIsPressed);
	}
}
