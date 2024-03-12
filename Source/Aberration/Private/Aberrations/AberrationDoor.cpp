// Fill out your copyright notice in the Description page of Project Settings.


#include "Aberrations/AberrationDoor.h"

#include "TrainDoor.h"

AAberrationDoor::AAberrationDoor() { }

void AAberrationDoor::Activate()
{
	Door->ForceOpenDoor();
}

void AAberrationDoor::Deactivate() { }