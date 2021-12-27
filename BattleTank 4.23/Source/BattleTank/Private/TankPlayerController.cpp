// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	if(GetControllerTank()) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *(GetControllerTank()->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing"))
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}



ATank* ATankPlayerController::GetControllerTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControllerTank()) { return; }
	FVector HitLocation; // will be the whole story at the end
	int32 ViewportX, ViewportY;
	GetViewportSize(ViewportX, ViewportY);
	auto ScreenLocation = FVector2D(ViewportX * CrosshairXLocation, ViewportY * CrosshairYLocation);
	FVector LookDirection;
	FVector CameraWorldLocation; // will be discarded
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection)) { // LookDirection will be now a unit vector depending on the crosshair
		FHitResult HitResult;
		auto StartLocation = PlayerCameraManager->GetCameraLocation();
		auto EndLocation = StartLocation + (LookDirection * LineTranceRange); // 10km
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
			HitLocation = HitResult.Location;
		}
		else { HitLocation = FVector(0); } // out of range, like sky
	
		GetControllerTank()->AimAt(HitLocation);
	}
}