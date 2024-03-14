// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AberrationCharacter.generated.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	void ToggleMoveAndLookInput(bool bEnable);
	void ToggleInteractiveWidget(bool bVisible) const;
	void ToggleMenuWidget(bool bVisible) const;
	void SetSensX(float Value);
	void SetSensY(float Value);
	void Pause(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

private:
	bool bCanMoveAndLook = true;
	bool bIsMenuOpen = false;
	
	UPROPERTY(EditDefaultsOnly, Category="Menu")
	TSubclassOf<UUserWidget> MenuClass;

	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	TSubclassOf<UUserWidget> InteractionClass;
	
	UPROPERTY()
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	TSubclassOf<UCameraShakeBase> CameraShake;
	
	UPROPERTY(EditDefaultsOnly, Category=Interaction)
	int InteractionRange = 0;

	IInteractive* CurrentInteractiveActor;
	void InteractionLineTrace();
	void SetInteractiveObject(IInteractive* Interactive);

	UPROPERTY(EditDefaultsOnly, Category=Input)
	float SensX;
	
	UPROPERTY(EditDefaultsOnly, Category=Input)
	float SensY;
};

