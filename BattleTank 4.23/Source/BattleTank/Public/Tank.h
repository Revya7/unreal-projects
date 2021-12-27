// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);


	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	void AimAt(FVector HitLocation);

private:
	float LaunchSpeed = 5000; // the max range we can hit, since u know, calculation

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;  // it's a pointer, instead of UClass*

	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditAnywhere, Category = Setup)
	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;
};