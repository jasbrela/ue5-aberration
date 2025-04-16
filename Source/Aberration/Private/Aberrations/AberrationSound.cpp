// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationSound.h"

#include "Components/AudioComponent.h"


AAberrationSound::AAberrationSound()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio");
	AudioComponent->SetAutoActivate(false);
	SetRootComponent(AudioComponent);
}

void AAberrationSound::BeginPlay()
{
	Super::BeginPlay();

	Deactivate();
}

void AAberrationSound::Activate()
{
	if (AudioComponent && AbnormalSFX)
	{
		AudioComponent->SetSound(AbnormalSFX);
		AudioComponent->Play();
	}
}

void AAberrationSound::Deactivate()
{
	if (AudioComponent && DefaultSFX)
	{
		AudioComponent->SetSound(DefaultSFX);
	}
}
