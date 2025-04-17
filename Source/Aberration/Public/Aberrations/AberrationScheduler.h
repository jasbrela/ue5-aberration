// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Aberrations/AberrationBase.h"
#include "GameFramework/Actor.h"
#include "AberrationScheduler.generated.h"

UCLASS()
class ABERRATION_API AAberrationScheduler : public AAberrationBase
{
	GENERATED_BODY()
	
public:	
	AAberrationScheduler();
	virtual void Activate() override;
	virtual void Deactivate() override;

protected:
	virtual void BeginPlay() override;

private:
	void Trigger();

	UPROPERTY(EditInstanceOnly, Category="Aberration")
	bool bScheduleActivation = true;

	UPROPERTY(EditInstanceOnly, Category="Aberration")
	int OverrideID = -1;
	
	UPROPERTY(EditInstanceOnly, Category= "Aberration")
	float DelayToTrigger;
	UPROPERTY(EditInstanceOnly, Category= "Aberration")
	bool bLoop;
	
	UPROPERTY(EditInstanceOnly)
	TArray<AAberrationBase*> Aberrations;
	
	FTimerHandle TimerHandle;
};
