// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/SettingsViewModel.h"

float USettingsViewModel::GetVolume() const { return Volume; }
float USettingsViewModel::GetSensX() const { return SensX; }
float USettingsViewModel::GetSensY() const { return SensY; }


void USettingsViewModel::SetVolume(float Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(Volume, Value)) {
		//UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetVolumePercent);
	}
}

void USettingsViewModel::SetSensX(float Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(SensX, Value)) {
		//UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetSensXPercent);
	}
}

void USettingsViewModel::SetSensY(float Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(SensY, Value)) {
		//UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetSensYPercent);
	}
}

