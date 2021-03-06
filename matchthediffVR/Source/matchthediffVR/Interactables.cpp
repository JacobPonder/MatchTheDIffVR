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
		OutlineMesh->AttachToComponent(BaseMesh,FAttachmentTransformRules::KeepRelativeTransform);
		
		OutlineMesh->SetRelativeScale3D(FVector(1.0));
		
	}
	if(!SolutionMesh)
	{
		SolutionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SolutionMesh"));
		SolutionMesh->SetWorldLocation(BaseMesh->GetComponentLocation()+DistanceBetweenHouses);
		
	}
	if(!SolutionOutlineMesh)
	{
		
		SolutionOutlineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SolutionOutlineMesh"));
		
		
		SolutionOutlineMesh->SetRelativeScale3D(FVector(1.0));
		
	}
}

// Called when the game starts or when spawned
void AInteractables::BeginPlay()
{
	Super::BeginPlay();
	OutlineMesh->SetVisibility(false);
	OutlineMesh->SetWorldLocation(BaseMesh->GetComponentLocation());
	SolutionOutlineMesh->SetVisibility(false);
	SolutionOutlineMesh->SetWorldLocation(BaseMesh->GetComponentLocation()+DistanceBetweenHouses);
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

