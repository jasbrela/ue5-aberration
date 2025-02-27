// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "SettingsViewModel.generated.h"

/**
 * 
 */
UCLASS()
class ABERRATION_API USettingsViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:	
	float GetSensX() const;
	float GetSensY() const;
	float GetVolume() const;
	
	UFUNCTION(BlueprintCallable)
	void SetSensX(float Value);
	UFUNCTION(BlueprintCallable)
	void SetSensY(float Value);
	UFUNCTION(BlueprintCallable)
	void SetVolume(float Value);


private:
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter, Getter)
	float SensX = 1.f;
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter, Getter)
	float SensY = 1.f;
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter, Getter)
	float Volume = 1.f;
};
