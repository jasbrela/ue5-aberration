#pragma once

#include "CoreMinimal.h"
#include "FActiveAberrations.generated.h"

USTRUCT(BlueprintType)
struct FActiveAberrations
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere)
	TArray<int> Array;
};
