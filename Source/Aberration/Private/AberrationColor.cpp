// Fill out your copyright notice in the Description page of Project Settings.


#include "AberrationColor.h"

#include "Aberration/DebugMacros.h"

AAberrationColor::AAberrationColor()
{
}

void AAberrationColor::BeginPlay()
{
	Super::BeginPlay();
}

void AAberrationColor::Notify()
{
	LOG("Notified (%i)", Value);
	Value++;
}
