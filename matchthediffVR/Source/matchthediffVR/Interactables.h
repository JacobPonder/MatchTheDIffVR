// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactables.generated.h"

UCLASS()
class MATCHTHEDIFFVR_API AInteractables : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractables();
	//meshes
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite, Category=Mesh)
	//base object
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite, Category=Mesh)
	//outline for base object
	UStaticMeshComponent* OutlineMesh;
	
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite, Category=Mesh)
	//clone of base object, spawned on the solution area
	UStaticMeshComponent* SolutionMesh;
	/**optional*/
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite, Category=Mesh)
	//outline for solution object
	UStaticMeshComponent* SolutionOutlineMesh;
	//vector used for to seperate the base and solution meshes
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite, Category=Mesh)
	FVector DistanceBetweenHouses = FVector(0,-5174.000000,0); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//highlight and  return self,
	//these let the player know when they are highlighting an interactible object
	void Highlighted();

	void UnHighlighted();
	//used when clicked
	UFUNCTION(BlueprintImplementableEvent)
	void OnActivate();

};
