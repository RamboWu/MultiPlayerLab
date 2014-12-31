// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MyProject4.h"
#include "MyProject4PlayerController.h"
#include "PlayerProxy.h"
#include "AI/Navigation/NavigationSystem.h"

AMyProject4PlayerController::AMyProject4PlayerController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMyProject4PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AMyProject4PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMyProject4PlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMyProject4PlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMyProject4PlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMyProject4PlayerController::MoveToTouchLocation);
}

void AMyProject4PlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AMyProject4PlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AMyProject4PlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	ServerSetNewMoveDestination(DestLocation);
	/*APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}*/
}

void AMyProject4PlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AMyProject4PlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

bool AMyProject4PlayerController::ServerSetNewMoveDestination_Validate(const FVector DestLocation)
{
	return true;
}

/* Actual implementation of the ServerSetMoveDestination method */
void AMyProject4PlayerController::ServerSetNewMoveDestination_Implementation(const FVector DestLocation)
{
	APlayerProxy* Pawn = Cast<APlayerProxy>(GetPawn());
	if (Pawn)
	{
		UNavigationSystem* const NaDemoys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NaDemoys && (Distance > 120.0f))
		{
			//NaDemoys-&gt;SimpleMoveToLocation(this, DestLocation);
			Pawn->MoveToLocation(this, DestLocation);
		}
	}
}
