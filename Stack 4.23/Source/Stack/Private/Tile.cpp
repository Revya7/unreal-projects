// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Spawner.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	SetSpawnerReference();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CanMove) {
		MoveMe(IsMovingX);
	}
}


void ATile::PlaceTile()
{
	CanMove = false;
	if (Spawner) {
		Spawner->ButtonClicked();
	}
}

void ATile::SetSpawnerReference()
{
	Spawner = Cast<ASpawner>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


