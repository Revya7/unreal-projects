// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class ASpawner;

UCLASS()
class STACK_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void MoveMe(bool IsMovingX);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DistanceToMove = 200;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanMove = false;

	UFUNCTION(BlueprintCallable)
	void PlaceTile();
	
	bool IsMovingX = true;

private:
	void SetSpawnerReference();
	ASpawner* Spawner = nullptr;

};
