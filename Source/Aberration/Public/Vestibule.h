// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Vestibule.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerChangeCoachDelegate);

UCLASS()
class ABERRATION_API AVestibule : public AActor
{
	GENERATED_BODY()
	
public:	
	AVestibule();
	virtual void Tick(float DeltaTime) override;
	static FOnPlayerChangeCoachDelegate PlayerChangeCoachDelegate;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditInstanceOnly)
	bool bCanTeleport;

	UPROPERTY(EditInstanceOnly)
	AVestibule* OtherVestibule;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FVector GetRelativePosition(FVector Offset);

	FVector GetOffset(AActor* Actor);
	
	FVector Location;
};
