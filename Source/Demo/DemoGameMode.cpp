// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "DemoGameMode.h"
#include "DemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADemoGameMode::ADemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/DemoCharacter_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void ADemoGameMode::BeginPlay()
{
}

void ADemoGameMode::Tick(float Deltatime)
{
}
