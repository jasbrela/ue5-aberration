// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "InteractionWidget.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class ABERRATION_API UInteractionWidget : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	UInteractionWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void ToggleTooltip(bool bInteractiveActorFound, const FText& Instruction);
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tooltip;
	UPROPERTY(meta = (BindWidget))
	UImage* Crosshair;
};