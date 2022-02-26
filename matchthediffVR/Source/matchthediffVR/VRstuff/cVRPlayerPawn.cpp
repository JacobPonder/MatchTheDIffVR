// Fill out your copyright notice in the Description page of Project Settings.


#include "cVRPlayerPawn.h"


// Sets default values
AcVRPlayerPawn::AcVRPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AcVRPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	CreateComponents();
}

// Called every frame
void AcVRPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AcVRPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AcVRPlayerPawn::CreateComponents()
{
	//The default root component for the pawn.
	USceneComponent* rootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = rootComponent;
 
	//Component that will be used for the movement based on input
	UFloatingPawnMovement* compFloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovementComp"));
 
	//Chaperone component that is required for Steam VR plugin
	USteamVRChaperoneComponent* chaperone = CreateDefaultSubobject<USteamVRChaperoneComponent>(TEXT("SteamVR Chaperone"));

	//Create a scene component that will act as the parent for the camera. This might come in handy later.
	USceneComponent* compVRCameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VR Camera Root"));
	compVRCameraRoot->SetupAttachment(rootComponent);
	compVRCameraRoot->SetRelativeLocationAndRotation(FVector::ZeroVector,FQuat::Identity);
	compVRCameraRoot->SetRelativeScale3D(FVector::OneVector);
 
	//Create a camera component and attach this to the camera root.
	UCameraComponent* compVRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("HMD Camera"));
	compVRCamera->SetupAttachment(compVRCameraRoot);
	compVRCamera->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
	compVRCamera->SetRelativeScale3D(FVector::OneVector);

	CreateHandController(compVRCameraRoot, "MC_Left", FXRMotionControllerBase::LeftHandSourceId);
	CreateHandController(compVRCameraRoot, "MC_Right",FXRMotionControllerBase::RightHandSourceId);

}

void AcVRPlayerPawn::CreateHandController(USceneComponent* a_compParent, FName a_strDisplayName, FName a_nameHandType)
{
	UMotionControllerComponent* compMotionController = CreateDefaultSubobject<UMotionControllerComponent>(a_strDisplayName);
	compMotionController->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
	compMotionController->SetRelativeScale3D(FVector::OneVector);
 
	compMotionController->MotionSource = a_nameHandType;
	compMotionController->SetupAttachment(a_compParent);
	FName strMeshDisplayName = a_nameHandType == FXRMotionControllerBase::LeftHandSourceId ? FName(TEXT("Hand_Left")) : FName(TEXT("Hand_Right"));
	CreateHandMesh(compMotionController, strMeshDisplayName, a_nameHandType);

}
UStaticMeshComponent* AcVRPlayerPawn::CreateHandMesh(UMotionControllerComponent* a_compParent, FName a_strDisplayName, FName a_nameHandType)
{
	
 
	//Find the default cube that ships with the engine content
	
	if (!CubeMeshObject)
	{
		//create the mesh component
		CubeMeshObject = CreateDefaultSubobject<UStaticMeshComponent>(a_strDisplayName);
		//set the mesh to the component
	
 
		//Set the defaults
		CubeMeshObject->SetAutoActivate(true);
		CubeMeshObject->SetVisibility(true);
		CubeMeshObject->SetHiddenInGame(false);
 
		//Set the root
		CubeMeshObject->SetupAttachment(a_compParent);
 
		CubeMeshObject->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
		FVector vec3Scale = FVector(0.25,0.25,0.25);
		CubeMeshObject->SetRelativeScale3D(vec3Scale);
 
		
	}
	return CubeMeshObject;
}
