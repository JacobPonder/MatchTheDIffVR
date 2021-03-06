// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables.h"
#include "PuzzleBase.generated.h"

/**
 * 
 */
UCLASS()
class MATCHTHEDIFFVR_API APuzzleBase : public AInteractables
{
	GENERATED_BODY()
	public:
	APuzzleBase();
	/**Identifier to determine what the solution checker checks*/
	UPROPERTY(BlueprintReadWrite)
	int StageNumber;
	UPROPERTY(BlueprintReadWrite)
	bool isCorrect;
};
