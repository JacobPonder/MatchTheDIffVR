// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalsManager.generated.h"

UCLASS()
class MATCHTHEDIFFVR_API APortalsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalsManager();

	//UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	//UBoxComponent* Puzzl;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
