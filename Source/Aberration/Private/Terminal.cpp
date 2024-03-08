// Fill out your copyright notice in the Description page of Project Settings.


#include "Terminal.h"

#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATerminal::ATerminal()
{
	PrimaryActorTick.bCanEverTick = false;

	TerminalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalMesh"));
	ScreenWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScreenWidget"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FocusCamera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	
	SetRootComponent(TerminalMesh);
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	ScreenWidget->SetupAttachment(RootComponent);
}

void ATerminal::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATerminal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UCameraComponent* ATerminal::GetFocusedCamera()
{
	return Camera;
}

