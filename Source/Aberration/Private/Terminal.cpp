// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Terminal.h"

#include "AberrationManager.h"
#include "UI/TerminalWidget.h"
#include "AberrationCharacter.h"
#include "AberrationGameState.h"
#include "AberrationPlayerController.h"
#include "DebugMacros.h"
#include "FAnswerData.h"
#include "Helper.h"
#include "MVVMGameSubsystem.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Types/MVVMViewModelContext.h"
#include "UI/TerminalViewModel.h"

class AAberrationManager;

ATerminal::ATerminal()
{
	PrimaryActorTick.bCanEverTick = !bDisable;

	TerminalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalMesh"));
	ScreenWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScreenWidget"));
	
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

void ATerminal::OnConfirmReport(int SelectedAnswerIndex)
{
	if (bIsBinaryQuestionActive && SelectedAnswerIndex == 0)
	{
		bIsBinaryQuestionActive = false;
		GenerateQuestion();
		return;
	}
	
	if (Answers[SelectedAnswerIndex].bIsCorrect)
	{
		TerminalVM->SetQuestionResultTexture(QuestionNumber-1, CorrectTexture);
	} else
	{
		TerminalVM->SetQuestionResultTexture(QuestionNumber-1, WrongTexture);
	}

	float Score = Answers[SelectedAnswerIndex].bIsCorrect ? 1.f : 0.f;

	/*for (int i = 0; i < Answers.Num(); i++)
	{
		LOG("Answer[%i].bIsCorrect: %hs", i, Answers[i].bIsCorrect ? "true" : "false");
		
		if (Answers[i].bIsCorrect)
		{
			LOG("Found Correct Answer: %i", i);
			Score += 1.f;
			
			//if (!bHasMultipleAnswers)
			//{
				break;
			//}
		}
	}*/
	
	State->RegisterScoreEntry(Score);	

	if (AberrationManager->WasLastCoach())
	{
		Character->DisableInput(Controller);
		// TODO: Show score result

		GetWorld()->GetTimerManager().SetTimer(LoadingTimerHandle, this, &ThisClass::ShowResults, 2.f, false);
		
		/*if (State)
		{
			State->SaveGame();
		}*/
		// Check QuestionnaireWidget::ConfirmReport for reference
	}
	
	//AberrationManager->OnConfirmReport();
	if (!bReportHandled)
	{
		OnReportHandled.Broadcast();
		bReportHandled = true;
	}
}

void ATerminal::ShowResults()
{
	if (State)
	{
		TerminalVM->SetupResultsScreen(State->GetFinalScorePercentage(), ScreenWidget->GetResultsDescription(State->GetPassed()));
	}
}

void ATerminal::BeginPlay()
{
	Super::BeginPlay();

	Tooltip = TooltipText;

	TerminalVM = NewObject<UTerminalViewModel>(UTerminalViewModel::StaticClass());

	for (int i = 0; i < 10; i++)
	{
		TerminalVM->SetQuestionResultTexture(i, DefaultTexture);
	}
	
	FMVVMViewModelContext Context;
	Context.ContextClass = UTerminalViewModel::StaticClass();
	Context.ContextName = TEXT("TerminalVM");

	const UMVVMGameSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UMVVMGameSubsystem>();
	auto PreviousInstance = Subsystem->GetViewModelCollection()->FindFirstViewModelInstanceOfType(UTerminalViewModel::StaticClass());
	
	//LOG("found previous mvvm - %hs", val == nullptr ? "false" : "true");
	
	if (PreviousInstance != nullptr)
	{
		Subsystem->GetViewModelCollection()->RemoveAllViewModelInstance(PreviousInstance);
	}
	
	Subsystem->GetViewModelCollection()->AddViewModelInstance(Context, TerminalVM);
	
	if (bDisable)
	{
		bIsInteractive = false;
		return;
	}
	
	ScreenWidget = Cast<UTerminalWidget>(ScreenWidgetComponent->GetWidget());
	
	ScreenWidget->OnConfirmReport = FOnConfirmReport::CreateUObject(this, &ThisClass::OnConfirmReport);

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
			AberrationManager = Manager;
			AberrationManager->ManagerUpdateAberrationsDelegate.AddDynamic(this, &ATerminal::UpdateReport);
			OnReportHandled.AddDynamic(AberrationManager, &AAberrationManager::OnConfirmReport);
		}
	}
	
	State = GetWorld()->GetGameState<AAberrationGameState>();
	State->SetTerminalVM(TerminalVM);
}

void ATerminal::Unfocus()
{
	if (bIsFocused) Interact();
}

void ATerminal::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ATerminal::Interact()
{
	//LOG("[%s] Interact", *GetActorLabel());

	if (Character->GetIsGamePaused()) return;
	
	bIsFocused = !bIsFocused;

	Character->ToggleMoveAndLookInput(!bIsFocused);
	Character->TogglePauseInput(!bIsFocused);
	
	//Controller->bShowMouseCursor = bIsFocused;

	int CoachIndex = AberrationManager->GetCurrentCoach();

	if (CoachIndex <= 1 && !bReportHandled)
	{
		bReportHandled = true;
		OnReportHandled.Broadcast();
	}
	
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
	bReportHandled = false;
	int CoachIndex = AberrationManager->GetCurrentCoach();
	LOG("Current Coach: %d", CoachIndex);
	
	if (!AberrationManager)
	{
		LOG("Aberration Manager is null");
	}
	
	if (CoachIndex <= 1)
	{
		TerminalVM->SetupOSUpdateScreen(ScreenWidget->GetOSScreenData(CoachIndex));

		//OnReportHandled.Broadcast();
		return;
	}

	ScreenWidget->UnlockButtons();
	
	const FActiveAberrations Previous = AberrationManager->GetPreviousActiveAberrations();
	PreviousAberrationsNames.Empty();
	
	if (!Previous.Array.IsEmpty() && AberrationManager)
	{
		for (int i = 0; i < AberrationManager->AberrationsData.Num(); i++)
		{
			if (Previous.Array.Contains(AberrationManager->AberrationsData[i]->ID))
			{
				PreviousAberrationsNames.AddUnique(AberrationManager->AberrationsData[i]->DisplayName.ToString());
			}
		}
	}
	
	if (State)
	{
		Stream = State->GetRandomStream();

		QuestionNumber++;
		TerminalVM->SetCurrentQuestionNumber(QuestionNumber);

		GenerateBinaryQuestion();
	}
}


void ATerminal::GenerateQuestion()
{
	Answers.Empty();
		
	TArray<FString> OtherAberrations = GetPreviousOtherThanActiveAberrationsNames();
	TArray<FString> CurrentAberrations = GetPreviousActiveAberrationsNames();

	TerminalVM->SetQuestionText(TextAberrationQuestion);
	ScreenWidget->bHasMultipleChoices = false;

	for (int i = 0; i < CurrentAberrations.Num(); i++)
	{
		LOG("Correct Answer = %i, %s", i, *CurrentAberrations[i]);
		Answers.Add(FAnswerData(CurrentAberrations[i], true));
	}
			
	for (int i = Answers.Num(); i < 3; i++)
	{
		const FString RandomAberration = OtherAberrations[Stream.RandRange(0, OtherAberrations.Num() - 1)];
		OtherAberrations.Remove(RandomAberration);
		LOG("Wrong Answer = %i, %s", i, *RandomAberration);

		Answers.AddUnique(FAnswerData(RandomAberration, false));
	}
	LOG("Total Answers = %i", Answers.Num());
		
	Answers = ShuffleArray(Answers, Stream);

	SetAnswersText();
}

void ATerminal::GenerateBinaryQuestion()
{
	Answers.Empty();

	const bool WasAnyAberrationGenerated = AberrationManager->WasAnyAberrationGenerated();
	
	Answers.AddUnique(FAnswerData(TextYes.ToString(), WasAnyAberrationGenerated));
	Answers.AddUnique(FAnswerData(TextNo.ToString(), !WasAnyAberrationGenerated));
	Answers.AddUnique(FAnswerData(TEXT(""), false));
	
	TerminalVM->SetQuestionText(TextBinaryQuestion);

	SetAnswersText();

	bIsBinaryQuestionActive = true;
}

void ATerminal::SetAnswersText()
{
	for (int i = 0; i < 3; i++)
	{
		TerminalVM->SetAnswerText(i, FText::FromString(Answers[i].Text));
	}
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
		//LOG("Other: %s", *AberrationManager->GetPreviousOtherThanActiveAberrations()[i]->DisplayName.ToString());
		Names.AddUnique(AberrationManager->GetPreviousOtherThanActiveAberrations()[i]->DisplayName.ToString());
	}
	
	return Names;
}
