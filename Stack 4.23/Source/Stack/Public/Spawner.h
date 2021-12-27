// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "Spawner.generated.h"

class ATile;
class UArrowComponent;

UCLASS()
class STACK_API ASpawner : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	void SpawnInitialeTile(int NumberOfTiles);
	void SpawnLeftOrRight(char Direction);

	UFUNCTION(BlueprintCallable)
	void SetArrowsReference(UArrowComponent* RightArrowToSet, UArrowComponent* LeftArrowToSet);
	
	UFUNCTION(BlueprintCallable)
	void MoveTile(ATile* TileToMove);

	UFUNCTION(BlueprintCallable)
	ATile* GetCurrentTile();

	UFUNCTION(BlueprintCallable)
	ATile* GetPreviousTile();

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnReminder(ATile* CurrentTile, ATile* PreviousTile,float DifferencePosition, bool IsMovingX);

	char DirectionToSpawn = 'l';
	bool IsMovingX = true;
	void SetNewTileScaleAndLocation();
	void IntersectScaleCal();
	void ButtonClicked();

private:
	void ElevateZ();
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<ATile> TileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<ATile> ReminderTileBlueprint;

	UPROPERTY(EditDefaultsOnly)
	int NumberOfTilesToSpawn = 10;

	int TileHeight = 10;
	UArrowComponent* RightArrow = nullptr;
	UArrowComponent* LeftArrow = nullptr;
	ATile* CurrentTile = nullptr;
	ATile* PreviousTile = nullptr;

};
