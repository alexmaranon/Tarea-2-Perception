// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_C_2GameMode.h"
#include "UTHUB_C_2Character.h"
#include "UObject/ConstructorHelpers.h"

AUTHUB_C_2GameMode::AUTHUB_C_2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
