// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s is missing PressurePlate"), *(GetOwner()->GetName()));
	}
	/// ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();  // So now when we play, tha AActor Actor than opens will be our default paun

}
/*
 void UOpenDoor::OpenDoor()
{
	// Getting the owner, we got it from a private method
	// FRotator OpenRotation = FRotator(0.0f, -65.0f, 0.0f);  // Making the rotation action (Rotator), Y-Z-X, f is for float, u have to specify it, or do it directly below
	/// if (!Owner) { return; }
	/// Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f)); // rotator name instead, inside ()
	OpenDoorEvent.Broadcast();
}
 */

/*
void UOpenDoor::CloseDoor()
{
	if (!Owner) { return; }
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}
*/


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// We gonna check if the ActorThatOpens is in the volume we open the door
	// will open any door that is connected to the Trigger

	if (GetTotalMassOfActorsOnPlate() > RequiredWeight) {     /// if((PressurePlate->IsOverlappingActor(ActorThatOpens)))
		OpenDoorEvent.Broadcast();
		LastDoorOpen = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() > (LastDoorOpen + DoorCloseDelay)) {
		CloseDoorEvent.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.0f;

	TArray<AActor*> OverlappingActors;  // finally introducing arrays
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);  // second param optional, give it an array and it will modify it by the actors on the plate
	for (auto* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();    // UPrimitiveComponent is where mass is stored, u can search it out
	}

	return TotalMass;
}

