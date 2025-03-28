// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/TerminalViewModel.h"

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
	if (UE_MVVM_SET_PROPERTY_VALUE(Seed, Value))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetSeedText);
	}
}

void UTerminalViewModel::SetupResultsScreen(const int32 Accuracy, const FText& Description)
{
	UE_MVVM_SET_PROPERTY_VALUE(AccuracyScore, FText::FromString(FString::Printf(TEXT("%d%%"), Accuracy)));
	UE_MVVM_SET_PROPERTY_VALUE(ResultsDescription, Description);
	UE_MVVM_SET_PROPERTY_VALUE(ShowResultsScreen, true);
}


void UTerminalViewModel::SetQuestionResultTexture(const int Index, UTexture2D* Texture)
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

void UTerminalViewModel::SetCurrentQuestionNumber(int32 Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentQuestionNumber, Value))
	{
		if (CurrentQuestionNumber == 1)
		{
			UE_MVVM_SET_PROPERTY_VALUE(ShowOSUpdateScreen, false);
		}
	}
}

void UTerminalViewModel::SetQuestionText(const FText& Value) {UE_MVVM_SET_PROPERTY_VALUE(QuestionText, Value); }

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
		UE_MVVM_SET_PROPERTY_VALUE(ShowThirdAnswerButton, !Value.IsEmpty());
	}
}

void UTerminalViewModel::SetupOSUpdateScreen(const FOSNotificationStateData& Data)
{
	UE_MVVM_SET_PROPERTY_VALUE(OSUpdateTitle, Data.TitleText);
	UE_MVVM_SET_PROPERTY_VALUE(OSUpdateBodyText, Data.BodyText);
	UE_MVVM_SET_PROPERTY_VALUE(OSUpdateImage, Data.ImageTexture);
	UE_MVVM_SET_PROPERTY_VALUE(OSUpdatePercentage, Data.UpdatePercentage);
}
