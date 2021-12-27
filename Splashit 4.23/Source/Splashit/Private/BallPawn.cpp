// Fill out your copyright notice in the Description page of Project Settings.

#include "BallPawn.h"

// Sets default values
ABallPawn::ABallPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABallPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABallPawn::BallOverlapped(FVector BoxLocation)
{
	if (MoveRight) {
		auto NewLocation = FVector(BoxLocation.X - FallBackDistance, GetActorLocation().Y, GetActorLocation().Z);
		SetActorLocation(NewLocation);
	}

	if (MoveLeft) {
		auto NewLocation = FVector(BoxLocation.X + FallBackDistance, GetActorLocation().Y, GetActorLocation().Z);
		SetActorLocation(NewLocation);
	}
	if (MoveUp) {
		auto NewLocation = FVector(GetActorLocation().X, BoxLocation.Y + FallBackDistance, GetActorLocation().Z);
		SetActorLocation(NewLocation);
	}
	if (MoveDown) {
		auto NewLocation = FVector(GetActorLocation().X, BoxLocation.Y - FallBackDistance, GetActorLocation().Z);
		SetActorLocation(NewLocation);
	}

	MoveRight = false;
	MoveLeft = false;
	MoveUp = false;
	MoveDown = false;
	CanMove = true;
	EnableInput(GetWorld()->GetFirstPlayerController());
}



void ABallPawn::IncrementAndCheckGameWon()
{
	TotalColoredGrounds = TotalColoredGrounds + 1;
	if (TotalColoredGrounds == TotalGrounds) {
		GameWon = true;
	}

}

void ABallPawn::DecreaseMaxMoves()
{
	MaxMoves = MaxMoves - 1;
	if (MaxMoves <= 0) {
		GameLost = true;
	}
}

