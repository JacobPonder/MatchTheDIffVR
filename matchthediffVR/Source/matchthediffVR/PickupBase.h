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
	/**Identifier to determine what the solution checker checks*/

	UPROPERTY(BlueprintReadWrite)
	bool IsPickedUp;
};
