// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Actor.h"
#include "Engine/TriggerVolume.h" // FOR TRIGGER VOLUME
#include "Engine/World.h" // FOR AUTO COMPLETE IN GetWorld()
#include "GameFramework/PlayerController.h" // FOR AUTO COMPLETE above->GetFirstPlayerController
#include "Engine/EngineTypes.h"
#include "Components/PrimitiveComponent.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

#define OUT

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/// void OpenDoor();
	/// void CloseDoor();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OpenDoorEvent;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent CloseDoorEvent;


// Everything from here down is written manually, adding a trigger
private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume * PressurePlate = nullptr; // can play with the naming here i guess, initialize all ptr to null and adjust them later THEY CRASH ALOT

	/// Each time u wanna use a pointer use this first if (!PointerName) { return; } , so it was nullprt u will leave the function instead of crash

	// UPROPERTY(EditAnywhere)  // The diff between removing the prop and not is making all doors open VS making only door that specifically can choose a specific Actor opens
	/// AActor * ActorThatOpens; // defining an Actor that we're gonna check for his presence in the Trigger

	AActor* Owner = GetOwner();

	
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.0f; // 1 second for now

	float LastDoorOpen;

	float GetTotalMassOfActorsOnPlate();
	UPROPERTY(EditAnywhere)
	float RequiredWeight = 20.0f;

};
