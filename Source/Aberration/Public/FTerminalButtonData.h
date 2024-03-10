#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "FTerminalButtonData.generated.h"

class UButton;

USTRUCT(BlueprintType)
struct FTerminalButtonData
{
	GENERATED_BODY()
	
public:
	[[deprecated("This constructor shouldn't be used. The variable Button will not be initialiazed.")]]
	FTerminalButtonData() : FTerminalButtonData(nullptr, nullptr) { }
	FTerminalButtonData(UButton* Button, UTextBlock* TextBlock) : Button(Button), TextBlock(TextBlock), bIsSelected(false), bIsCorrect(false) { }

	void SetText(const FString& Text) const
	{
		TextBlock->SetText(FText::FromString(Text));
	}

	void ToggleVisibility(bool Visible) const
	{
		Button->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
	
	UPROPERTY()
	UButton* Button;

	UPROPERTY()
	UTextBlock* TextBlock;

	bool bIsSelected;
	bool bIsCorrect;
};