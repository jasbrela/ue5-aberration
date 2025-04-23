// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "SettingsViewModel.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangeShakeIntensityDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangePreferredCultureDelegate);

UCLASS()
class ABERRATION_API USettingsViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:	
	float GetSensX() const;
	float GetSensY() const;
	float GetVolume() const;
	float GetShakeIntensity() const;
	FString GetPreferredCulture() const;
	
	UFUNCTION(BlueprintCallable)
	void SetSensX(float Value);
	UFUNCTION(BlueprintCallable)
	void SetSensY(float Value);
	UFUNCTION(BlueprintCallable)
	void SetVolume(float Value);
	UFUNCTION(BlueprintCallable)
	void SetShakeIntensity(float Value);
	UFUNCTION(BlueprintCallable)
	void SetPreferredCulture(FString Value);
	
	FOnChangeShakeIntensityDelegate OnChangeShakeIntensity;
	FOnChangePreferredCultureDelegate OnChangePreferredCulture;
	
private:
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter, Getter)
	float SensX = 1.f;
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter, Getter)
	float SensY = 1.f;
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter, Getter)
	float Volume = 1.f;
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter, Getter)
	float ShakeIntensity = 1.f;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter, Getter)
	FString PreferredCulture = "en";
};
