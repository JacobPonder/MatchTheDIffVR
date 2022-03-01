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

void AcVRPlayerPawn::CacheHandAnimInstances()
{
	m_refLeftHandAnimBP = Cast<UcPlayerHandAnimBP>(m_meshLeftHand->GetAnimInstance());
	if (!IsValid(m_refLeftHandAnimBP))
		UE_LOG(LogTemp, Error, TEXT("Could not cast Hand Anim to the right class"));
	m_refRightHandAnimBP = Cast<UcPlayerHandAnimBP>(m_meshRightHand->GetAnimInstance());
	if (!IsValid(m_refRightHandAnimBP))
		UE_LOG(LogTemp, Error, TEXT("Could not cast Hand Anim to the right class"));
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
	InputComponent->BindAction("GripLeft", IE_Pressed, this, &AcVRPlayerPawn::GripLeftHand_Pressed);
	InputComponent->BindAction("GripRight", IE_Pressed, this, &AcVRPlayerPawn::GripRightHand_Pressed);
	InputComponent->BindAction("GripLeft", IE_Released, this, &AcVRPlayerPawn::GripLeftHand_Released);
	InputComponent->BindAction("GripRight", IE_Released, this, &AcVRPlayerPawn::GripRightHand_Released);

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
	//Create the hand mesh for visualization
	FName strMeshDisplayName = a_nameHandType == FXRMotionControllerBase::LeftHandSourceId ? FName(TEXT("Hand_Left")) : FName(TEXT("Hand_Right"));
	USkeletalMeshComponent* refHandMesh = CreateHandMesh(compMotionController, strMeshDisplayName, a_nameHandType);
	if (a_nameHandType == FXRMotionControllerBase::LeftHandSourceId)
		m_meshLeftHand = refHandMesh;
	else
		m_meshRightHand = refHandMesh;
}


USkeletalMeshComponent* AcVRPlayerPawn::CreateHandMesh(UMotionControllerComponent* a_compParent, FName a_strDisplayName, FName a_nameHandType)
{
	
 
	//Find the default cube that ships with the engine content
	USkeletalMeshComponent* refComponentHand = NULL;
 
	//Find the default cube that ships with the engine content
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> HandMeshObject(TEXT("SkeletalMesh'/Game/VirtualReality/Mannequin/Character/Mesh/MannequinHand_Right.MannequinHand_Right'"));
	if (!HandMeshObject.Object)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not load the default cube for hand mesh"));
		return NULL;
	}
	if (!refComponentHand)
	{
		//create the mesh component
		refComponentHand = CreateDefaultSubobject<USkeletalMeshComponent>(a_strDisplayName);
		//set the mesh to the component
		refComponentHand->SetSkeletalMesh(HandMeshObject.Object,true);
	
 
		//Set the defaults
		refComponentHand->SetAutoActivate(true);
		refComponentHand->SetVisibility(true);
		refComponentHand->SetHiddenInGame(false);
 
		//Set the root
		refComponentHand->SetupAttachment(a_compParent);
 
		refComponentHand->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
		FVector vec3Scale = FVector(0.25,0.25,0.25);
		refComponentHand->SetRelativeScale3D(vec3Scale);
		SetHandAnimationBlueprint(refComponentHand);
		
	}
	return refComponentHand;
}

void AcVRPlayerPawn::SetHandAnimationBlueprint(USkeletalMeshComponent* a_refHand)
{
	static ConstructorHelpers::FObjectFinder<UClass> HandAnimBP(TEXT("AnimBlueprintGeneratedClass'/Game/VirtualReality/Mannequin/Animations/RightHand_AnimBP.RightHand_AnimBP_C'"));
	if (HandAnimBP.Succeeded())
	{
		a_refHand->AnimClass = HandAnimBP.Object;
		a_refHand->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		a_refHand->SetAnimInstanceClass(HandAnimBP.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not load the hand anim BP"));
	}
}
void AcVRPlayerPawn::GripLeftHand_Pressed_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Left Hand Grip Pressed"));
	m_refLeftHandAnimBP->SetGripValue(1.0f);
}
void AcVRPlayerPawn::GripRightHand_Pressed_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Right Hand Grip Pressed"));
	m_refRightHandAnimBP->SetGripValue(1.0f);

}
void AcVRPlayerPawn::GripLeftHand_Released_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Left Hand Grip Released"));
	m_refLeftHandAnimBP->SetGripValue(0.0f);

}
void AcVRPlayerPawn::GripRightHand_Released_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Left Hand Grip Released"));
	m_refRightHandAnimBP->SetGripValue(0.0f);

}