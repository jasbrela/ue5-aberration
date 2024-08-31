// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/QuestionButton.h"

UQuestionButton::UQuestionButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UQuestionButton::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UQuestionButton::IsAnswerCorrect() const
{
	return bIsPressed && bIsCorrect;
}

void UQuestionButton::SetIsCorrect(bool IsCorrect)
{
	bIsCorrect = IsCorrect;
}
