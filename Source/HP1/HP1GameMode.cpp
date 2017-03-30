// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "HP1.h"
#include "HP1GameMode.h"
#include "HP1Character.h"

AHP1GameMode::AHP1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
