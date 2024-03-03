#pragma once

#include "CoreMinimal.h"
#include "FAberrationData.generated.h"

USTRUCT(BlueprintType)
struct FAberrationData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ID = 0;

	// Use 0 for unlocked from start.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int UnlockAfterCoach = 0;
};
