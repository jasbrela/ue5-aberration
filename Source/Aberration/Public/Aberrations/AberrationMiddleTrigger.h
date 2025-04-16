// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AberrationMiddleTrigger.generated.h"

struct FActiveAberrations;
class AAberrationManager;
class UBoxComponent;

UCLASS()
class ABERRATION_API AAberrationMiddleTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AAberrationMiddleTrigger();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	bool bIsActive = true;
	
	UFUNCTION()
	void Activate(FActiveAberrations _);
	
	UPROPERTY(EditInstanceOnly)
	UBoxComponent* Trigger;

	UPROPERTY()
	AAberrationManager* Manager;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
