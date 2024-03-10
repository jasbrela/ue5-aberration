#pragma once

#include "CoreMinimal.h"
#include "FAnswerData.generated.h"

class UButton;

USTRUCT(BlueprintType)
struct FAnswerData
{
	GENERATED_BODY()
	
public:
	FAnswerData() : FAnswerData("N/A", false) { }
	FAnswerData(const FString& Text, const bool IsCorrect) : Text(Text), bIsCorrect(IsCorrect) { }

	FString Text;
	bool bIsCorrect;

	bool operator==(const FAnswerData& Other) const
	{
		return Other.Text == Text;
	}

	bool operator!=(const FAnswerData& Other) const
	{
		return Other.Text != Text;
	}
};