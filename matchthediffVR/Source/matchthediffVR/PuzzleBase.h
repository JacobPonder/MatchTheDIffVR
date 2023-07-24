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
	//used by the solution checker to indicate wether or not the puzzle needs to be looked at for the current stage. 
	UPROPERTY(BlueprintReadWrite)
	int StageNumber;
	//used by the solution checker to let it know when the puzzle is its correct state
	UPROPERTY(BlueprintReadWrite)
	bool isCorrect;
};
