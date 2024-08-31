// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactive.generated.h"

UINTERFACE(MinimalAPI)
class UInteractive : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ABERRATION_API IInteractive
{
	GENERATED_BODY()

public:
	bool bIsInteractive = true;
	
	FString Tooltip = "Interact";
	
	virtual void OnEnterRange() = 0;
	virtual void Interact() = 0;
	virtual void OnExitRange() = 0;
private:
};