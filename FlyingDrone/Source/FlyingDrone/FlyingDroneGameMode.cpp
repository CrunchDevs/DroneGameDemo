// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FlyingDroneGameMode.h"
#include "FlyingDronePawn.h"

AFlyingDroneGameMode::AFlyingDroneGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AFlyingDronePawn::StaticClass();
}
