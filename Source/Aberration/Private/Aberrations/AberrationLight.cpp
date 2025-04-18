// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationLight.h"

#include "DebugMacros.h"
#include "Components/LightComponent.h"
#include "Engine/Light.h"

AAberrationLight::AAberrationLight()
{
	//Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	//SetRootComponent(Light);
}

void AAberrationLight::BeginPlay()
{
	Super::BeginPlay();

	if (Light)
	{
		DefaultIntensity = Light->GetLightComponent()->Intensity;
	}
}

void AAberrationLight::Activate()
{
	if (Light)
	{
		Light->GetLightComponent()->SetIntensity(AbnormalIntensity);
	}
}

void AAberrationLight::Deactivate()
{
	if (Light)
	{
		Light->GetLightComponent()->SetIntensity(DefaultIntensity);
		LOG("Deactivated Light");
	}
}
