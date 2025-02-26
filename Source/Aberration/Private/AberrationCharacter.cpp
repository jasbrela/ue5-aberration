// Copyright Epic Games, Inc. All Rights Reserved.

#include "AberrationCharacter.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "UI/InteractionWidget.h"
#include "Interactive.h"
#include "AberrationGameState.h"
#include "UI/MenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AAberrationCharacter

AAberrationCharacter::AAberrationCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void AAberrationCharacter::InteractionLineTrace()
{
	const UWorld* World = GetWorld();
	
	if (World == nullptr) return;
	
	FVector TraceStart = GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector TraceEnd = TraceStart + GetFirstPersonCameraComponent()->GetForwardVector() * InteractionRange;
	
	FHitResult Hit;
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	World->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, QueryParams);
	
	//DrawDebugLine(World, TraceStart, TraceEnd, FColor::Orange, false);

	AActor* ActorHit = Hit.GetActor();
	
	if (Hit.bBlockingHit && IsValid(ActorHit))
	{
		if (IInteractive* Interactive = Cast<IInteractive>(ActorHit))
		{
			if (CurrentInteractiveActor != Interactive) {
				
				if (Interactive->bIsInteractive)
				{
					SetInteractiveObject(Interactive);
					CurrentInteractiveActor->OnEnterRange();
				} else
				{
					SetInteractiveObject(nullptr);
				}
			}
			else if (!CurrentInteractiveActor->bIsInteractive)
			{
				SetInteractiveObject(nullptr);
			}
		}
	} else
	{
		SetInteractiveObject(nullptr);
	}
}

void AAberrationCharacter::SetInteractiveObject(IInteractive* Interactive)
{
	if (CurrentInteractiveActor == Interactive) return;
	//LOG("SetInteractiveObject, %s, %s", (CurrentInteractiveActor == nullptr ? TEXT("nullptr") : TEXT("actor")), (CurrentInteractiveActor == nullptr ? TEXT("nullptr") : TEXT("actor")));

	if (CurrentInteractiveActor != nullptr)
	{
		CurrentInteractiveActor->OnExitRange();
	}

	CurrentInteractiveActor = Interactive;

	if (CurrentInteractiveActor != nullptr)
	{
		CurrentInteractiveActor->OnEnterRange();
	}

	const bool IsInteractiveValid = CurrentInteractiveActor != nullptr;
	const FString Tooltip = IsInteractiveValid ? CurrentInteractiveActor->Tooltip : TEXT("");
	InteractionWidget->ToggleTooltip(IsInteractiveValid, Tooltip);
		
	//FString TooltipText = CurrentInteractiveActor != nullptr ? TEXT("[E] " + Interactive->Tooltip) : TEXT("");
	//InteractionWidget->ToggleTooltip(CurrentInteractiveActor != nullptr, TooltipText);
}

void AAberrationCharacter::Interact(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact !! A"));
	//if (!Value.Get<bool>()) return;
	UE_LOG(LogTemp, Warning, TEXT("Interact !! B"));
	
	if (CurrentInteractiveActor)
	{
	UE_LOG(LogTemp, Warning, TEXT("Interact !! C"));
		CurrentInteractiveActor->Interact();
	}
}

void AAberrationCharacter::Sprint(const FInputActionValue& Value)
{

	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}

void AAberrationCharacter::StopSprinting(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}

void AAberrationCharacter::ToggleMoveAndLookInput(bool bEnable)
{
	bCanMoveAndLook = bEnable;

	if (bCanMoveAndLook)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
	} else
	{
		PlayerController->SetInputMode(FInputModeGameAndUI());
	}
}

void AAberrationCharacter::ToggleInteractiveWidget(bool bVisible) const
{
	InteractionWidget->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void AAberrationCharacter::ToggleMenuWidget(bool bVisible) const
{
	MenuWidget->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void AAberrationCharacter::SetSensX(float Value)
{
	SensX = Value;
}

void AAberrationCharacter::SetSensY(float Value)
{
	SensY = Value;
}

void AAberrationCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const UWorld* World = GetWorld())
	{
		if (InteractionClass)
		{
			InteractionWidget = CreateWidget<UInteractionWidget>(UGameplayStatics::GetPlayerController(World, 0),
																 InteractionClass, TEXT("InteractionUI"));
			InteractionWidget->AddToViewport(0);
		}

		if (MenuClass)
		{
			MenuWidget = CreateWidget<UMenuWidget>(UGameplayStatics::GetPlayerController(World, 0),
																 MenuClass, TEXT("MenuUI"));

			ToggleMenuWidget(false);
			MenuWidget->Inject(this);
			
			MenuWidget->AddToViewport(0);
			
			if (AAberrationGameState* State = World->GetGameState<AAberrationGameState>())
			{
				MenuWidget->Inject(State);
			}
		}
	}
	
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		PlayerController = PC;
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (CameraShake)
	{
		UGameplayStatics::GetPlayerCameraManager(this, 0)->StartCameraShake(CameraShake);
	}

	ToggleMoveAndLookInput(true);
}

void AAberrationCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InteractionLineTrace();
}

//////////////////////////////////////////////////////////////////////////// Input

void AAberrationCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAberrationCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAberrationCharacter::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AAberrationCharacter::Interact);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AAberrationCharacter::Pause);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AAberrationCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AAberrationCharacter::StopSprinting);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AAberrationCharacter::Pause(const FInputActionValue& Value)
{
	if (!bCanPause) return;
	if (!Value.Get<bool>()) return;
	
	bIsMenuOpen = !bIsMenuOpen;

	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = bIsMenuOpen;
	}
	
	ToggleMoveAndLookInput(!bIsMenuOpen);
	ToggleMenuWidget(bIsMenuOpen);
}

void AAberrationCharacter::TogglePauseInput(bool bEnable)
{
	bCanPause = bEnable;
}

void AAberrationCharacter::Move(const FInputActionValue& Value)
{
	if (!bCanMoveAndLook) return;
	
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AAberrationCharacter::Look(const FInputActionValue& Value)
{
	if (!bCanMoveAndLook) return;

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X * SensX);
		AddControllerPitchInput(LookAxisVector.Y * SensY);
	}
}