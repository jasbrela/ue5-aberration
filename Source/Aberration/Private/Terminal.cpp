// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Terminal.h"

#include "AberrationManager.h"
#include "UI/TerminalWidget.h"
#include "AberrationCharacter.h"
#include "AberrationPlayerController.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

class AAberrationManager;

ATerminal::ATerminal()
{
	PrimaryActorTick.bCanEverTick = !bDisable;

	TerminalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalMesh"));
	ScreenWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScreenWidget"));

	Tooltip = TEXT("Fill Report");
	
	SetRootComponent(TerminalMesh);
	ScreenWidgetComponent->SetupAttachment(RootComponent);
}

void ATerminal::OnExitRange()
{
	if (bIsFocused)
	{
		Interact();
	}
	
	ScreenWidgetComponent->SetVisibility(false);
}

void ATerminal::OnEnterRange()
{
	ScreenWidgetComponent->SetVisibility(true);
}

void ATerminal::BeginPlay()
{
	Super::BeginPlay();
	
	if (bDisable)
	{
		bIsInteractive = false;
		return;
	}
	
	ScreenWidget = Cast<UTerminalWidget>(ScreenWidgetComponent->GetWidget());

	if (ACharacter* BaseCharacter = UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		Character = Cast<AAberrationCharacter>(BaseCharacter);
		
		if (Character)
		{
			AController* BaseController = Character->GetController();
			Controller = Cast<AAberrationPlayerController>(BaseController);
		}
	}

	if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), AAberrationManager::StaticClass()); Actor != nullptr)
	{
		if (AAberrationManager* Manager = Cast<AAberrationManager>(Actor))
		{
			//LOG("%s   SET MANAGER", *GetActorLabel());
			AberrationManager = Manager;
			AberrationManager->ManagerUpdateAberrationsDelegate.AddDynamic(this, &ATerminal::UpdateReport);
			ScreenWidget->Inject(AberrationManager);
		}
	}

	if (ScreenWidget)
	{
		ScreenWidget->Inject(ScreenWidgetComponent);
		ScreenWidget->Inject(this);
	}
}

void ATerminal::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ATerminal::Interact()
{
	//LOG("[%s] Interact", *GetActorLabel());

	bIsFocused = !bIsFocused;

	Character->ToggleMoveAndLookInput(!bIsFocused);
	Character->TogglePauseInput(!bIsFocused);
	
	Controller->bShowMouseCursor = bIsFocused;
	
	if (bIsFocused)
	{
		Controller->SetViewTargetWithBlend(FocusActor, .75f);
	} else
	{
		Controller->SetViewTargetWithBlend(Character, .25f);
	}

	Character->ToggleInteractiveWidget(!bIsFocused);
	
	//GetFocusedCamera()->SetActive(bIsFocused);
}

void ATerminal::UpdateReport(FActiveAberrations Aberrations)
{
	if (!AberrationManager)
	{
		LOG("Aberration Manager is null");
	}
	
	if (AberrationManager->GetCurrentCoach() <= 1)
	{
		ConfirmReport();
		return;
	}
	
	const FActiveAberrations Previous = AberrationManager->GetPreviousActiveAberrations();
	PreviousAberrationsNames.Empty();
	
	if (!Previous.Array.IsEmpty() && AberrationManager)
	{
		for (int i = 0; i < AberrationManager->AberrationsData.Num(); i++)
		{
			if (Previous.Array.Contains(AberrationManager->AberrationsData[i]->ID))
			{
				PreviousAberrationsNames.AddUnique(AberrationManager->AberrationsData[i]->AberrationName);
			}
		}
	}
	
	if (ScreenWidget)
	{
		ScreenWidget->ShowReport();
	}
}

void ATerminal::ConfirmReport() const
{
	if (AberrationManager->WasLastCoach())
	{
		Character->DisableInput(Controller);
		return;
	}

	PlayerFillReportDelegate.Broadcast();
}

TArray<FString> ATerminal::GetPreviousActiveAberrationsNames()
{
	return PreviousAberrationsNames;
}

TArray<FString> ATerminal::GetPreviousOtherThanActiveAberrationsNames() const
{
	TArray<FString> Names;
	
	for (int i = 0; i < AberrationManager->GetPreviousOtherThanActiveAberrations().Num(); i++)
	{
		//LOG("Other: %s", *AberrationManager->GetPreviousOtherThanActiveAberrations()[i]->AberrationName);
		Names.AddUnique(AberrationManager->GetPreviousOtherThanActiveAberrations()[i]->AberrationName);
	}
	
	return Names;
}
