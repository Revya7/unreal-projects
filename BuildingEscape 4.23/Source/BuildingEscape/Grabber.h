// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h" // For Input Component, didnt really need it tho
#include "Engine/World.h" // FOR AUTO COMPLETE IN GetWorld()
#include "GameFramework/PlayerController.h" // FOR AUTO COMPLETE above->GetFirstPlayerController
#include "Public/DrawDebugHelpers.h" // For DrawDebugLine()
#include "Engine/EngineTypes.h" // For FHitResult.GetComponent()->
#include "Components/PrimitiveComponent.h"  // For FHitResult.GetComponent()->
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private: 
	float Reach = 100.0f;
	UPhysicsHandleComponent* PhysicsHandler = nullptr;  // we declare it here as null, we assign it in the game start
	UInputComponent* InputComponent = nullptr;			// doing the same for the input component, u know binding or mapping keys

	// Ray-cast and pick the object
	void Grab();
	void Release();
	void FindPhysicsHandler();
	void SetupInputComponent();
	FHitResult GetFirstBodyInReach();  // Returning void here worked, but we needed a hit to get the component of the hit result, for use in the built in "grabber"
	FVector GetLineTraceEnd();
	FVector GetPlayerViewPointLocation(); // to solve a problem made by making the function above, u know scope shit
};
