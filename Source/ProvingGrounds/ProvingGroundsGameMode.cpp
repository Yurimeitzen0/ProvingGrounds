// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ProvingGroundsGameMode.h"
#include "ProvingGroundsHUD.h"
#include "ProvingGroundsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProvingGroundsGameMode::AProvingGroundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Character/Blueprints/TP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProvingGroundsHUD::StaticClass();
}
