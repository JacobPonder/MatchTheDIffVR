// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "cPlayerHandAnimBP.generated.h"

/**
 * 
 */
UCLASS()
class MATCHTHEDIFFVR_API UcPlayerHandAnimBP : public UAnimInstance
{
	GENERATED_BODY()
public:
	UcPlayerHandAnimBP(const FObjectInitializer& ObjectInitializer);
	UFUNCTION()
	virtual void SetGripValue(float a_fGrip);
	UFUNCTION()
	virtual float GetGripValue();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blend")
	float m_fGripVal;
};
