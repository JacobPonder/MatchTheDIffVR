// Fill out your copyright notice in the Description page of Project Settings.


#include "cVRPlayerPawn.h"


// Sets default values
AcVRPlayerPawn::AcVRPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AcVRPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AcVRPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AcVRPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

