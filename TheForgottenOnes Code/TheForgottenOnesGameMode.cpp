// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TheForgottenOnesGameMode.h"
#include "TheForgottenOnesHUD.h"
#include "TheForgottenOnesCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheForgottenOnesGameMode::ATheForgottenOnesGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATheForgottenOnesHUD::StaticClass();
}
