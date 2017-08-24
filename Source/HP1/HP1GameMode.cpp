// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "HP1.h"
#include "HP1GameMode.h"
#include "HP1Character.h"
#include "Blueprint/UserWidget.h"


AHP1GameMode::AHP1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BluePrints/Characters/MyBPCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}