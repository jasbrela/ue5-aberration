// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TerminalButton.h"
#include "TaskbarButton.generated.h"

class UWidgetComponent;

class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class ABERRATION_API UTaskbarButton : public UTerminalButton
{
	GENERATED_BODY()

public:
	UTaskbarButton(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY(meta = (BindWidget))
	UImage* WindowIcon;
};
