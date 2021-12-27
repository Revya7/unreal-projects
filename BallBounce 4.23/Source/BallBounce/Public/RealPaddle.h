// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RealPaddle.generated.h"

class ABall;
class UArrowComponent;

UCLASS()
class BALLBOUNCE_API ARealPaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARealPaddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Ball)
	bool isBallLaunched = false;
	
	UPROPERTY(BlueprintReadWrite, Category = Ball)
	ABall* myBall;
	
	UPROPERTY(BlueprintReadWrite, Category = Ball)
	UArrowComponent* ballPositionArrow;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Speed)
	float paddleSpeed = 20;

	UFUNCTION(BlueprintCallable, Category = Movement)
	void HandleMovement(float axisValue);

};