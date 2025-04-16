// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AAberrationMiddleTrigger.generated.h"

class UBoxComponent;

UCLASS()
class ABERRATION_API AAAberrationMiddleTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AAAberrationMiddleTrigger();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditInstanceOnly)
	UBoxComponent* Trigger;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
