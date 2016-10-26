// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;

	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the Out Launch Velocity.
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		WorldSpaceAim,
		LaunchSpeed,
		false, 
		0, 
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Aim solve found."));
		MoveBarrel(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No aim solve found."));
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	// Work out difference between current barrel rotation, and aim direction

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());

	Barrel->Elevate(5.0f);
}
