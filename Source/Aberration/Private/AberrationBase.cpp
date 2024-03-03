// Fill out your copyright notice in the Description page of Project Settings.


#include "AberrationBase.h"

#include "Vestibule.h"

// Sets default values
AAberrationBase::AAberrationBase()
{
	AVestibule::PlayerChangeCoachDelegate.AddDynamic(this, &AAberrationBase::Notify);
}

void AAberrationBase::Notify() { }
