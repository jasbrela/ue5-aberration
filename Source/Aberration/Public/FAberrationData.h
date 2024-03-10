#pragma once

#include "CoreMinimal.h"
#include "DebugMacros.h"
#include "FAberrationData.generated.h"

USTRUCT(BlueprintType)
struct FAberrationData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ID = 0;
	
	// To be displayed in the Terminal
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AberrationName = TEXT("N/A");
	
	// Use 0 for unlocked from start.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int UnlockAfterCoach = 0;


	bool operator==(const FAberrationData &Other) const
	{
		//LOG("OPERATOR ==");
		return ID == Other.ID;
	}
	
	bool operator!=(const FAberrationData &Other) const
	{
		//LOG("OPERATOR !=");
		return ID == Other.ID;
	}

	bool operator==(const int OtherID) const
	{
		return ID == OtherID;
	}
};
