// Fill out your copyright notice in the Description page of Project Settings.

#include "Ball.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABall::BallOverlapped(FVector BoxLocation)
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
	if (GameWon) {
		UE_LOG(LogTemp, Warning, TEXT("You won"));
	}
	CanMove = true;
	EnableInput(GetWorld()->GetFirstPlayerController());
}



void ABall::IncrementAndCheckGameWon()
{
	TotalColoredGrounds = TotalColoredGrounds + 1;
	if (TotalColoredGrounds == TotalGrounds) {
		GameWon = true;
	}

}

void ABall::DecreaseMaxMoves()
{
	MaxMoves = MaxMoves - 1;
	UE_LOG(LogTemp, Warning, TEXT("Changed"));
	if (MaxMoves <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("You Loose"));
	}
}

