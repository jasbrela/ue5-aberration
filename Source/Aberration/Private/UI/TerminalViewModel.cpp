// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/TerminalViewModel.h"

int32 UTerminalViewModel::GetCurrentQuestionNumber() const { return CurrentQuestionNumber; }
FText UTerminalViewModel::GetQuestionText() const { return QuestionText; }
FText UTerminalViewModel::GetAnswerText1() const { return AnswerText1; }
FText UTerminalViewModel::GetAnswerText2() const { return AnswerText2; }
FText UTerminalViewModel::GetAnswerText3() const { return AnswerText3; }

FText UTerminalViewModel::GetSeedText() const
{
	return FText::FromString(FString::Printf(TEXT("OS-%i"), Seed));
}

void UTerminalViewModel::SetLocalMousePosition(FVector2D Position)
{
	UE_MVVM_SET_PROPERTY_VALUE(LocalMousePosition, Position);
}

void UTerminalViewModel::SetSeed(const int32 Value)
{
	UE_MVVM_SET_PROPERTY_VALUE(Seed, Value);
}


void UTerminalViewModel::SetQuestionTexture(int Index, UTexture2D* Texture)
{
	switch (Index)
	{
		case 0:
			UE_MVVM_SET_PROPERTY_VALUE(QuestionTexture0, Texture);
			break;
		case 1:
			UE_MVVM_SET_PROPERTY_VALUE(QuestionTexture1, Texture);
			break;
		case 2:
			UE_MVVM_SET_PROPERTY_VALUE(QuestionTexture2, Texture);
			break;		
		case 3:
			UE_MVVM_SET_PROPERTY_VALUE(QuestionTexture3, Texture);
			break;		
		case 4:
			UE_MVVM_SET_PROPERTY_VALUE(QuestionTexture4, Texture);
			break;		
		case 5:
			UE_MVVM_SET_PROPERTY_VALUE(QuestionTexture5, Texture);
			break;		
		case 6:
			UE_MVVM_SET_PROPERTY_VALUE(QuestionTexture6, Texture);
			break;		
		case 7:
			UE_MVVM_SET_PROPERTY_VALUE(QuestionTexture7, Texture);
			break;		
		case 8:
			UE_MVVM_SET_PROPERTY_VALUE(QuestionTexture8, Texture);
			break;
		case 9:
			UE_MVVM_SET_PROPERTY_VALUE(QuestionTexture9, Texture);
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Failed to set QuestionTexture: Invalid Index"));
			break;
	}
}

void UTerminalViewModel::SetCurrentQuestionNumber(int32 Value) { UE_MVVM_SET_PROPERTY_VALUE(CurrentQuestionNumber, Value); }

void UTerminalViewModel::SetQuestionText(const FText& Value) { UE_MVVM_SET_PROPERTY_VALUE(QuestionText, Value); }

void UTerminalViewModel::SetAnswerText(int Index, const FText& Value)
{
	if (Index == 0)
	{
		UE_MVVM_SET_PROPERTY_VALUE(AnswerText1, Value);
	} else if (Index == 1)
	{
		UE_MVVM_SET_PROPERTY_VALUE(AnswerText2, Value);
	} else
	{
		UE_MVVM_SET_PROPERTY_VALUE(AnswerText3, Value);
	}
}
