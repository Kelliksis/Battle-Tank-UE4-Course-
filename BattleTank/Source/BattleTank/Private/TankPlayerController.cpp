// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing %s."), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

/* Start the tank moving the barrel so that a shot would hit where the cros intersects with the world. */
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector HitLocation; // OUT Param.

	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace.
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

		// Get world location via line trace
		// it hits something
		// Tell controlled tank to aim at the point hit
	}
}

/* Returns an OUT param, if true */
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{

	HitLocation = FVector(1.0);

	return true;

}
