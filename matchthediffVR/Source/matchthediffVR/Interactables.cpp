// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables.h"

// Sets default values
AInteractables::AInteractables()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if(!BaseMesh)
	{
		BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
		
	}
	if(!OutlineMesh)
	{
		OutlineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OutlineMesh"));
		OutlineMesh->SetVisibility( false);
		
	}
	if(!SolutionMesh)
	{
		SolutionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SolutionMesh"));
		SetActorLocation(BaseMesh->GetRelativeLocation()+DistanceBetweenHouses);
		
	}
	if(!SolutionOutlineMesh)
	{
		
		SolutionOutlineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SolutionOutlineMesh"));
		SolutionOutlineMesh->SetVisibility(false);
		SetActorLocation(BaseMesh->GetComponentLocation()+DistanceBetweenHouses);
		
	}
}

// Called when the game starts or when spawned
void AInteractables::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractables::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractables::Highlighted()
{
	OutlineMesh->SetVisibility(true);
}

void AInteractables::UnHighlighted()
{
	OutlineMesh->SetVisibility(false);
}
