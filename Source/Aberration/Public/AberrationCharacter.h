// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AberrationCharacter.generated.h"

class AAberrationGameState;
class ATerminal;
class UMenuWidget;
class UInteractionWidget;
class IInteractive;
class UInteractionComponent;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AAberrationCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAberrationCharacter();
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	void ToggleMoveAndLookInput(bool bEnable);
	void ToggleInteractiveWidget(bool bVisible) const;
	void ToggleMenuWidget(bool bVisible) const;
	void SetSensX(float Value);
	void SetSensY(float Value);
	void Pause(const FInputActionValue& Value);
	void TogglePauseInput(bool bEnable);
	void ListenToSettingsEvents();
	bool GetIsGamePaused();

	UFUNCTION()
	void UpdateCameraShake();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Unfocus(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void StopSprinting(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

private:
	bool bCanMoveAndLook = true;
	bool bIsMenuOpen = false;
	bool bCanPause = true;

	UPROPERTY()
	AAberrationGameState* State;
	
	UPROPERTY()
	ATerminal* Terminal;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	float SprintSpeedMultiplier = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Menu")
	TSubclassOf<UUserWidget> MenuClass;

	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	TSoftClassPtr<UUserWidget> InteractionClass;

	UFUNCTION()
	void OnInteractionClassLoaded();
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UInteractionWidget* InteractionWidget;

	UPROPERTY()
	UMenuWidget* MenuWidget;
	
	UPROPERTY(VisibleInstanceOnly)
	APlayerController* PlayerController;
	
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* UnfocusAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	TSubclassOf<UCameraShakeBase> CameraShake;
	
	UPROPERTY(EditDefaultsOnly, Category=Interaction)
	int InteractionRange = 0;

	IInteractive* CurrentInteractiveActor;
	void InteractionLineTrace();
	void SetInteractiveObject(IInteractive* Interactive);

	UPROPERTY()
	UCameraShakeBase* ShakeInstance;

	UFUNCTION()
	void LocaliseTooltip();

	UPROPERTY(EditDefaultsOnly, Category=Input)
	float SensX;
	
	UPROPERTY(EditDefaultsOnly, Category=Input)
	float SensY;
};

