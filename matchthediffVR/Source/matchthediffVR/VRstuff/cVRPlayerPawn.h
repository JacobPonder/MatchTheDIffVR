// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "cPlayerHandAnimBP.h"
#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "HeadMountedDisplay.h"
#include "SteamVRChaperoneComponent.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "matchthediffVR/Interactables.h"
#include "Blueprint/UserWidget.h"
#include "cVRPlayerPawn.generated.h"



	

UCLASS()
class MATCHTHEDIFFVR_API AcVRPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AcVRPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	
	bool IsHighlighting = false;
 	AInteractables* CurHighlighted;
	
	
	void CacheHandAnimInstances();
	
	
	//other
	
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* m_meshLeftHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* m_meshRightHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UcPlayerHandAnimBP* m_refLeftHandAnimBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UcPlayerHandAnimBP* m_refRightHandAnimBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* compVRCameraRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* compVRCamera;
	/*
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* compPlayerOutline;*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool inPuzzleHouse = true;
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite, Category=Mesh)
	FVector DistanceBetweenHouses = FVector(0,-5174.000000,0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetInteractionComponent* menuInteract;
	
	
	//Teleporting Variables and Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent* TPDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* TPSpline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TPEndPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TPCylinder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TPRing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TPArrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TPRoomScaleMesh;
	
	FVector TpLocation;
	bool TPrequest= false;
	TArray<USplineMeshComponent*> SplineMeshs;
	bool IsTPchecking = false;
	bool IsTPValid = false;
	float TPLaunchVelocity = 900.0;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	void CreateComponents();

	void CreateHandController(USceneComponent* a_compParent, FName a_strDisplayName, FName a_nameHandType);


	
	USkeletalMeshComponent* CreateHandMesh(UMotionControllerComponent* a_compParent, FName a_strDisplayName,FName a_nameHandType);

	void SetHandAnimationBlueprint(USkeletalMeshComponent* a_refHand);

	UFUNCTION (BlueprintNativeEvent, Category = "Input")
	void GripLeftHand_Pressed();
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void GripRightHand_Pressed();
	UFUNCTION (BlueprintNativeEvent, Category = "Input")
	void GripLeftHand_Released();
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void GripRightHand_Released();
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void TP_Player();
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void TP_Houses();
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void Return_to_main();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void TP_Ready();
	//UFUNCTION(BlueprintNativeEvent, Category = "Teleport")
	void ClearArc();
	//UFUNCTION(BlueprintNativeEvent, Category = "Teleport")
	void UpdateSpline(bool haveValidLocation, TArray<FPredictProjectilePathPointData> SplinePoints );
	//UFUNCTION(BlueprintNativeEvent, Category = "Teleport")
	void UpdateEndpoint(bool haveValidLocation, FVector NewLocation);
};



