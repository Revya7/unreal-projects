// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#define OUT  // does nothing at all

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandler();
	SetupInputComponent();
	UE_LOG(LogTemp, Warning, TEXT("Grabber pawn on duty!"));
	
}


void UGrabber::FindPhysicsHandler()
{
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandler == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Physics Handler Not found on %s"), *(GetOwner()->GetName()));
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>(); // only appears on game start tho

	if (InputComponent == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Input Component Not found on %s"), *(GetOwner()->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Input Component is found and on duty!"));

		// The action name from the engine, the event name, the obj u wanna add shit on i guess, then name a function for now, define it somewhere in header without the USomething (& for address)
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Release", IE_Released, this, &UGrabber::Release);
	}

}

FHitResult UGrabber::GetFirstBodyInReach()
{
	
	FVector LineTraceEnd = GetLineTraceEnd();
	// So u'r basically giving 2 empty values for a function to modify them, so let's make a micro just to nmayez between them

	FVector PlayerViewPointLocation = GetPlayerViewPointLocation();

	/// Logging our postion and rotation each frame : UE_LOG(LogTemp, Warning, TEXT("Location: %s and the Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());




	// Getting the hit from the laser (ray-cast)

	///  there's many other types of this tracing, like multi or by something else

	// Setup the Hit obj
	FHitResult Hit;
	// Setup query parameters
	FCollisionQueryParams AdditionalParams(FName(TEXT("")), false, GetOwner());   // Forget the TagName , false bcz we want simple collision, GetOwner() to ignore ourselves, the grabber

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		AdditionalParams // just naming tho
	);

	// What we get from Hit
	AActor* TargetHit = Hit.GetActor(); // Getting the Actor that was hit, DONT CREATE an FString outisde the if Statement, it will crash

	// NOW LOOK AT THAT BABY, WE CAN USE IF ON ACTORS TO CHECK PRESENCE, EVEN IF IT'S NOT A BOOLLLLLL
	if (TargetHit) {
		UE_LOG(LogTemp, Warning, TEXT("The object %s was hit by the laser!"), *(TargetHit->GetName()));
	}

	return Hit;
}

FVector UGrabber::GetLineTraceEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;  // Rotation is a Rotator not a Vector, Reach is to make the result vector longer
}

FVector UGrabber::GetPlayerViewPointLocation()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}


void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab function is called"));

	if (!PhysicsHandler) { return; }

	auto HitResult = GetFirstBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit) {

		PhysicsHandler->GrabComponent(
			ComponentToGrab,  // the component of the hit result
			NAME_None,		  // no bones
			ComponentToGrab->GetOwner()->GetActorLocation(),  // the obj u wanna grap location, that's the white ball in the object, worked even with error
			true  // allow rotation
		);
	}

	/// NOW TIME TO GO CONFIGURE THE TICK TO MOVE THE OBJ
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Release function is called"));
	if (!PhysicsHandler) { return; }
	PhysicsHandler->ReleaseComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandler) { return; }
	if (PhysicsHandler->GrabbedComponent) { // built in methods grabbed, be sure to set the location

		FVector NewLocation = GetLineTraceEnd();
		PhysicsHandler->SetTargetLocation(NewLocation); // We set the location
	}
}

/*  DRAWING A RED TRACE, WAS IN TICK
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255,0,0), // RED
		false, // Persistent line
		0.0f, // it's not presistent so life time is useless,
		0.0f, // in front, or idk, doesnt matter for now,
		10.0f // thickness 10 cm
	);
*/
