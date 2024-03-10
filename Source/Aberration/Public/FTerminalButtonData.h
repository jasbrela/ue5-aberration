#pragma once

#include "CoreMinimal.h"
#include "FTerminalButtonData.generated.h"

class UButton;

USTRUCT(BlueprintType)
struct FTerminalButtonData
{
	GENERATED_BODY()
	
public:
	[[deprecated("This constructor shouldn't be used. The variable Button will not be initialiazed.")]]
	FTerminalButtonData() : FTerminalButtonData(nullptr) { }
	FTerminalButtonData(UButton* button) : Button(button), bIsSelected(false), bIsCorrect(false) { }
	
	UPROPERTY()
	UButton* Button;

	bool bIsSelected;
	bool bIsCorrect;
};