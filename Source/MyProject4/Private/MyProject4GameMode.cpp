// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MyProject4.h"
#include "MyProject4GameMode.h"
#include "MyProject4PlayerController.h"
#include "MyProject4Character.h"
#include "PlayerProxy.h"

AMyProject4GameMode::AMyProject4GameMode(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP)
{
	// use our custom PlayerController class
	PlayerControllerClass = AMyProject4PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/

	DefaultPawnClass = APlayerProxy::StaticClass();
}