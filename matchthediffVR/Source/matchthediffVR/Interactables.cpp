// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables.h"
//This is the base for all interactable objects in the game. 
// Sets default values
AInteractables::AInteractables()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//this makes the base mesh the root component
	if(!BaseMesh)
	{
		BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
		SetRootComponent(BaseMesh);
	}
	//this attches the Outline mesh the root component
	if(!OutlineMesh)
	{
		OutlineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OutlineMesh"));
		OutlineMesh->AttachToComponent(BaseMesh,FAttachmentTransformRules::KeepRelativeTransform);
		
		OutlineMesh->SetRelativeScale3D(FVector(1.0));
		OutlineMesh->SetWorldLocation(BaseMesh->GetComponentLocation());
	}
	//this creates the solution meshl, and makes sure its the appropriate distance from the base mesh
	if(!SolutionMesh)
	{
		SolutionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SolutionMesh"));
		SolutionMesh->SetWorldLocation(BaseMesh->GetComponentLocation()+DistanceBetweenHouses);
		
	}
	//this creates the solution mesh outline, if applicable,
	if(!SolutionOutlineMesh)
	{
		
		SolutionOutlineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SolutionOutlineMesh"));
		SolutionOutlineMesh->SetWorldLocation(SolutionMesh->GetComponentLocation());
		
		SolutionOutlineMesh->SetRelativeScale3D(FVector(1.0));
		
	}
}

// Called when the game starts or when spawned
void AInteractables::BeginPlay()
{
	Super::BeginPlay();
	OutlineMesh->SetVisibility(false);
	
	SolutionOutlineMesh->SetVisibility(false);
	
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

