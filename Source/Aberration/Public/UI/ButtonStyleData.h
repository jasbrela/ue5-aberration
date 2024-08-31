// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ButtonStyleData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ABERRATION_API UButtonStyleData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FButtonStyle Style;
};
