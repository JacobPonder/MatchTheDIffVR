// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables.h"
#include "PickupBase.generated.h"

/**
 * 
 */
UCLASS()
class MATCHTHEDIFFVR_API APickupBase : public AInteractables
{
	GENERATED_BODY()
	public:
	APickupBase();
	//makes the item "dissapear" when picked up
	UPROPERTY(BlueprintReadWrite)
	bool IsPickedUp;
	// image, associated with the pickup,that lets the player know theyve picked the item up
	UPROPERTY(BlueprintReadWrite)
	UTexture2D* InventoryImage; ;
};
