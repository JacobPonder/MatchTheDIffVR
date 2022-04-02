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
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite, Category=Mesh)
	UStaticMeshComponent* OutlineMesh;
	
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite, Category=Mesh)
	UStaticMeshComponent* SolutionMesh;
	/**optional*/
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite, Category=Mesh)
	UStaticMeshComponent* SolutionOutlineMesh;
	//other
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite, Category=Mesh)
	FVector DistanceBetweenHouses = FVector(0,-5174.000000,0); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//highlight and  return self
	void Highlighted();

	void UnHighlighted();
	//used when clicked
	UFUNCTION(BlueprintImplementableEvent)
	void OnActivate();

};
