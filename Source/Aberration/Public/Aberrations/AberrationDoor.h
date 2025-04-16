// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Aberrations/AberrationBase.h"
#include "AberrationDoor.generated.h"

class ATrainDoor;
/**
 * 
 */
UCLASS()
class ABERRATION_API AAberrationDoor : public AAberrationBase
{
	GENERATED_BODY()
public:
	AAberrationDoor();
	virtual void Activate() override;
	virtual void Deactivate() override;
	
private:
	UPROPERTY(EditInstanceOnly)
	ATrainDoor* Door;
};
