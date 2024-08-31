// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationLight.h"

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
	//LOG("%s: Activate", *GetActorLabel())
	if (Light)
	{
		//LOG("Hello!? %f", AbnormalIntensity);
		Light->GetLightComponent()->SetIntensity(AbnormalIntensity);
	}
}

void AAberrationLight::Deactivate()
{
	//LOG("%s: Deactivate", *GetActorLabel())
	if (Light)
	{
		Light->GetLightComponent()->SetIntensity(DefaultIntensity);
	}
}
