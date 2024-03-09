// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainDoor.h"

#include "AberrationManager.h"
#include "Terminal.h"
#include "Aberration/AberrationCharacter.h"
#include "Aberration/DebugMacros.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ATrainDoor::ATrainDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	ForceCloseTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ForceCloseTrigger"));
	ClosedDoorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ClosedDoorCollision"));

	Tooltip = TEXT("Open");
	
	SetRootComponent(DoorMesh);
	ForceCloseTrigger->SetupAttachment(RootComponent);
	ClosedDoorCollision->SetupAttachment(RootComponent);
}

void ATrainDoor::BeginPlay()
{
	Super::BeginPlay();

	ForceCloseTrigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

	if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATerminal::StaticClass()); Actor != nullptr)
	{
		if (ATerminal* Terminal = Cast<ATerminal>(Actor))
		{
			Terminal->PlayerFillReportDelegate.AddDynamic(this, &ATrainDoor::ReleaseAccess);
		}
	}
}

void ATrainDoor::DoorMovement(float DeltaTime)
{	
	const float DoorCurrentPosition = DoorMesh->GetRelativeLocation().Y;
	const float FinalLocation = bIsOpening ? ClosedDoorYLocation : OpenDoorYLocation;

	//LOG("Current RelativePos: %f | %f", DoorCurrentPosition, FinalLocation);

	const bool NearlyEqual = FMath::IsNearlyEqual(DoorCurrentPosition, FinalLocation, 1.f);
	const bool OffLimits = (bIsOpening && DoorCurrentPosition > FinalLocation) || (!bIsOpening && DoorCurrentPosition < FinalLocation);

	if (NearlyEqual || OffLimits)
	{
		this->bIsMoving = false;
		return;
	}

	const float YOffsetToAdd = (bIsOpening ? OpenSpeed : CloseSpeed) * DeltaTime * (bIsOpening ? 1 : -1);
	
	const FVector LocationToAdd = FVector(0, YOffsetToAdd, 0);
	DoorMesh->AddRelativeLocation(LocationToAdd);
}

void ATrainDoor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CloseDoor();
}

void ATrainDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving)
	{
		DoorMovement(DeltaTime);
	}
}

void ATrainDoor::OpenDoor()
{
	if (bIsOpening) return;
	
	bIsOpening = true;
	bIsMoving = true;
	
	ClosedDoorCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATrainDoor::CloseDoor()
{
	if (!bIsOpening) return;
	
	bIsOpening = false;
	bIsMoving = true;
	
	ClosedDoorCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ATrainDoor::Interact()
{
	OpenDoor();
	bIsInteractive = false;
}

void ATrainDoor::OnExitRange() { }

void ATrainDoor::OnEnterRange() { }

void ATrainDoor::ReleaseAccess()
{
	bIsInteractive = true;
}

