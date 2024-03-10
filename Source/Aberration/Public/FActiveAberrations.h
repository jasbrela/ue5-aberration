#pragma once

#include "CoreMinimal.h"
#include "FActiveAberrations.generated.h"

USTRUCT(BlueprintType)
struct FActiveAberrations
{
	GENERATED_BODY()
	
public:
	FActiveAberrations();
	
	UPROPERTY(VisibleAnywhere)
	TArray<int> Array;
};

inline FActiveAberrations::FActiveAberrations()
{
	Array.SetNum(0);
}
