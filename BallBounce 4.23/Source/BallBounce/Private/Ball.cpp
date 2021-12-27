// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}


FVector ABall::CalculateRotator(FVector linearVel, FRotator& RotateBy)
{
	auto currentRotation = linearVel.Rotation().Yaw;
	float newRotation = roundf((linearVel.Rotation().Yaw + 45)/ 90) * 90 - 45;
	RotateBy = FRotator(0, newRotation - currentRotation, 0);

	return linearVel;
}



float ABall::ReturnSign(float num) 
{
	if (num < 0) return -1.0f;
	return 1.0f;
}

