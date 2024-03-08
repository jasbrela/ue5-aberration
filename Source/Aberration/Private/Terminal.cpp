// Fill out your copyright notice in the Description page of Project Settings.


#include "Terminal.h"

#include "Aberration/AberrationCharacter.h"
#include "Aberration/AberrationPlayerController.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

ATerminal::ATerminal()
{
	PrimaryActorTick.bCanEverTick = false;

	TerminalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalMesh"));
	ScreenWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScreenWidget"));
	
	SetRootComponent(TerminalMesh);
	ScreenWidget->SetupAttachment(RootComponent);
}

void ATerminal::OnExitRange()
{
	ScreenWidget->SetVisibility(false);
}

void ATerminal::OnEnterRange()
{
	ScreenWidget->SetVisibility(true);
}

void ATerminal::BeginPlay()
{
	Super::BeginPlay();

	if (ACharacter* BaseCharacter = UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		Character = Cast<AAberrationCharacter>(BaseCharacter);
		
		if (Character)
		{
			AController* BaseController = Character->GetController();
			Controller = Cast<AAberrationPlayerController>(BaseController);
		}
	}
}

void ATerminal::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ATerminal::Interact()
{
	//LOG("[%s] Interact", *GetActorLabel());

	bIsFocused = !bIsFocused;

	Controller->SetIgnoreMoveInput(bIsFocused);
	Controller->SetIgnoreLookInput(bIsFocused);
	Controller->bShowMouseCursor = bIsFocused;
	
	if (bIsFocused)
	{
		Controller->SetViewTargetWithBlend(FocusActor, 1);
	} else
	{
		Controller->SetViewTargetWithBlend(Character, 1);
	}
	
	//GetFocusedCamera()->SetActive(bIsFocused);	
}

