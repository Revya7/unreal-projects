// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"


UCLASS()
class SPLASHIT_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void BallOverlapped(FVector BoxLocation);

	UFUNCTION(BlueprintCallable)
	void IncrementAndCheckGameWon();

	UFUNCTION(BlueprintCallable)
	void DecreaseMaxMoves();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitialSpeed = 800;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FallBackDistance = 105; // 100 + n

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TotalGrounds = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TotalColoredGrounds = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxMoves = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanMove = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GameWon = false;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MoveRight = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MoveLeft = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MoveUp = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MoveDown = false;

};
