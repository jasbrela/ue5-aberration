// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationDoor.h"

#include "TrainDoor.h"

AAberrationDoor::AAberrationDoor() { }

void AAberrationDoor::Activate()
{
	Door->BlockNextForceClose();
	Door->ForceOpenDoor();
}

void AAberrationDoor::Deactivate() { }