#pragma once

#include "CoreMinimal.h"
#include "FOSNotificationStateData.generated.h"

class UImage;

USTRUCT(BlueprintType)
struct FOSNotificationStateData
{
	GENERATED_BODY()
	
public:
	FOSNotificationStateData()
	{
		ImageTexture = nullptr;
		TitleText = FText::FromString(TEXT("PLACEHOLDER"));
		BodyText = FText::FromString(TEXT("If you are seeing this text, please report this bug!"));
		UpdatePercentage = 0.0f;
	}

	UPROPERTY(EditAnywhere)
    UTexture2D* ImageTexture;

    UPROPERTY(EditAnywhere)
    FText TitleText;
	
	UPROPERTY(EditAnywhere, meta = (MultiLine = true))
    FText BodyText;
    
	UPROPERTY(EditAnywhere)
	float UpdatePercentage;
};
