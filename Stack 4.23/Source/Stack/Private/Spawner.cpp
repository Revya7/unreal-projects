// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "Tile.h"
#include "Engine/World.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnInitialeTile(NumberOfTilesToSpawn);
	SpawnLeftOrRight(DirectionToSpawn);
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpawner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ASpawner::SetArrowsReference(UArrowComponent* RightArrowToSet, UArrowComponent* LeftArrowToSet)
{
	RightArrow = RightArrowToSet;
	LeftArrow = LeftArrowToSet;
}


void ASpawner::SpawnInitialeTile(int NumberOfTiles)
{
	for (int i = 0; i < NumberOfTiles; i++) {
		PreviousTile = GetWorld()->SpawnActor<ATile>(TileBlueprint, GetActorLocation(), GetActorRotation());
		ElevateZ();
	}
}

void ASpawner::ElevateZ()
{
	SetActorLocation(FVector(0, 0, GetActorLocation().Z + TileHeight));
}

void ASpawner::SpawnLeftOrRight(char Direction)
{
	if (CurrentTile) {
		PreviousTile = CurrentTile;
	}
	if (RightArrow && LeftArrow) {
		FVector ArrowLocation;
		FRotator ArrowRotation;
		if (Direction == 'r') {
			ArrowLocation = RightArrow->GetComponentLocation();
			ArrowRotation = RightArrow->GetComponentRotation();
			DirectionToSpawn = 'l';
			IsMovingX = false;
		}
		else {
			ArrowLocation = LeftArrow->GetComponentLocation();
			ArrowRotation = LeftArrow->GetComponentRotation();
			DirectionToSpawn = 'r';
			IsMovingX = true;
		}
		CurrentTile = GetWorld()->SpawnActor<ATile>(TileBlueprint, ArrowLocation, ArrowRotation);
		MoveTile(CurrentTile);
		ElevateZ();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("One of the Arrow's reference at least is not set wtf"));
	}
}


void ASpawner::MoveTile(ATile* TileToMove)
{
	if (TileToMove) {
		TileToMove->IsMovingX = IsMovingX;
		TileToMove->CanMove = true;
	}
}
	


ATile* ASpawner::GetCurrentTile()
{
	return CurrentTile;
}


ATile* ASpawner::GetPreviousTile()
{
	return PreviousTile;
}


void ASpawner::SetNewTileScaleAndLocation()
{
	auto SetToX = PreviousTile->GetActorScale3D().Y;
	auto SetToY = PreviousTile->GetActorScale3D().X;
	CurrentTile->SetActorScale3D(FVector(SetToX, SetToY, CurrentTile->GetActorScale3D().Z));
	if (!IsMovingX) {
		auto NewLocationX = PreviousTile->GetActorLocation().X;
		CurrentTile->SetActorLocation(FVector(NewLocationX, CurrentTile->GetActorLocation().Y, CurrentTile->GetActorLocation().Z));
	}
	else {
		auto NewLocationY = PreviousTile->GetActorLocation().Y;
		CurrentTile->SetActorLocation(FVector(CurrentTile->GetActorLocation().X, NewLocationY, CurrentTile->GetActorLocation().Z));
	}
}


void ASpawner::IntersectScaleCal()
{
	FVector CurrentScale = CurrentTile->GetActorScale3D();
	FVector CurrentLocation = CurrentTile->GetActorLocation();
	if (IsMovingX) {
		float CurrentLocationX = CurrentLocation.X;
		float PreviousLocationX = PreviousTile->GetActorLocation().X;
		float PreviousScaleY = PreviousTile->GetActorScale3D().Y;
		float NewScaleX = PreviousScaleY - (abs(CurrentLocationX - PreviousLocationX) / 100);
		float NewLocationX = (CurrentLocationX + PreviousLocationX) / 2;
		CurrentTile->SetActorScale3D(FVector(NewScaleX, CurrentScale.Y, CurrentScale.Z));
		CurrentTile->SetActorLocation(FVector(NewLocationX, CurrentLocation.Y, CurrentLocation.Z));
		SpawnReminder(CurrentTile, PreviousTile, (CurrentLocationX - PreviousLocationX)/100, IsMovingX);
	}
	else {
		float CurrentLocationY = CurrentLocation.Y;
		float PreviousLocationY = PreviousTile->GetActorLocation().Y;
		float PreviousScaleY = PreviousTile->GetActorScale3D().Y;
		auto NewScaleX = PreviousScaleY - (abs(CurrentLocationY - PreviousLocationY) / 100);
		float NewLocationY = (CurrentLocationY + PreviousLocationY) / 2;
		CurrentTile->SetActorScale3D(FVector(NewScaleX, CurrentScale.Y, CurrentScale.Z));
		CurrentTile->SetActorLocation(FVector(CurrentLocation.X, NewLocationY, CurrentLocation.Z));
		SpawnReminder(CurrentTile, PreviousTile, (CurrentLocationY - PreviousLocationY)/100, IsMovingX);
	}
}



void ASpawner::ButtonClicked()
{
	IntersectScaleCal();
	SpawnLeftOrRight(DirectionToSpawn);
	SetNewTileScaleAndLocation();
}


