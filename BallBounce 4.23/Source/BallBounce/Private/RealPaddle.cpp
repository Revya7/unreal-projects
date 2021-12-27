// Fill out your copyright notice in the Description page of Project Settings.


#include "RealPaddle.h"
#include "Ball.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"


// Sets default values
ARealPaddle::ARealPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ARealPaddle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ARealPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ARealPaddle::HandleMovement(float axisValue)
{
	if (axisValue < 0.0f || axisValue > 0.0f) {
		AddActorWorldOffset(FVector(axisValue * paddleSpeed, 0.0f, 0.0f), true);
		if (!isBallLaunched) {
			if (!ballPositionArrow || !myBall) {
				UE_LOG(LogTemp, Warning, TEXT("ballPositionArrow or myBall pointer are null"));
			}
			myBall->SetActorLocation(ballPositionArrow->GetComponentLocation());
		}
	}
}

