// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyProject4PlayerController.h"
#include "PlayerProxy.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT4_API APlayerProxy : public APawn
{
	GENERATED_UCLASS_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera) 
	TSubobjectPtr<class UCameraComponent> TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera) 
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	// Needed so we can pick up the class in the constructor and spawn it elsewhere 
	TSubclassOf<AActor> CharacterClass;

	// Pointer to the actual character. We replicate it so we know its location for the camera on the client 
	UPROPERTY(Replicated) 
	class AMyProject4Character* Character;

	// The AI Controller we will use to auto-navigate the player 
	class AAIController* PlayerAI;

	// We spawn the real player character and other such elements here 
	virtual void BeginPlay() override;

	// Use do keep this actor in sync with the real one 
	void Tick(float DeltaTime);

	// Used by the controller to get moving to work 
	void MoveToLocation(const AMyProject4PlayerController* controller, const FVector& vector);
};

