// Fill out your copyright notice in the Description page of Project Settings.


#include "cVRPlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include <dsound.h>


//#include "AssetSelection.h"
#include "matchthediffVR/Interactables.h"
#include "matchthediffVR/PickupBase.h"
#include "matchthediffVR/PuzzleBase.h"


// Sets default values
AcVRPlayerPawn::AcVRPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CreateComponents();
	
}

// Called when the game starts or when spawned
void AcVRPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	//CreateComponents();
	
	
	menuInteract->bShowDebug = true;
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
//get meshes, if ovelap is interactable, call highlight,set bool to true, else set bool to false

	// trace params required for line trace, ignore actor prevents from hitting itself
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);	// owning player is ignored
	TraceParams.AddIgnoredComponent(m_meshRightHand);	// hands are ignored
	TraceParams.AddIgnoredComponent(m_meshLeftHand);	// hands are ignored
	
	// initialize hit info
	FHitResult HitResult;
	FVector end = m_meshRightHand->GetForwardVector() * 1000;
	
	bool HadHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		m_meshRightHand->GetComponentLocation(),
		m_meshRightHand->GetComponentLocation() + end,
		ECC_Visibility,
		TraceParams);
	//DrawDebugLine(GetWorld(),m_meshRightHand->GetComponentLocation(),m_meshRightHand->GetComponentLocation() + end/* HitResult.Location*/,FColor::Red,false,0.1);
	//compPointer->ArrowLength = (m_meshRightHand->GetComponentLocation() + end).Size();
	//printf("%f",compPointer->ArrowLength);

	if(HadHit)
	{
		
		AInteractables* selected = Cast<AInteractables>(HitResult.Actor);
		if(selected)
		{
			
			//TPrequest = false;
			APickupBase* Pickup = Cast<APickupBase>(HitResult.Actor);
			APuzzleBase* Puzzle = Cast<APuzzleBase>(HitResult.Actor);
			if(Pickup)
			{
				if(Pickup->IsPickedUp)
				{
					
				}
				else
				{
				
					if(CurHighlighted!=selected)
					{
						if(CurHighlighted)
						{
							CurHighlighted->UnHighlighted();
						}
						selected->Highlighted();
						CurHighlighted = selected;
					}
					IsHighlighting = true;
				}
			}
			else if(Puzzle)
			{
					if(CurHighlighted!=selected)
					{
						if(CurHighlighted)
						{
							CurHighlighted->UnHighlighted();
						}
						selected->Highlighted();
						CurHighlighted = selected;
					}
					IsHighlighting = true;
			}
			else
			{
				//if not puzzle or pickup
				if(CurHighlighted!=selected)
				{
					if(CurHighlighted)
					{
						CurHighlighted->UnHighlighted();
					}
					selected->Highlighted();
					CurHighlighted = selected;
				}
				IsHighlighting = true;
				
			}
			
		}
		else
		{
			if(CurHighlighted)
			{
				CurHighlighted->UnHighlighted();
				CurHighlighted = nullptr;
				IsHighlighting = false;
			}
			//TpLocation = HitResult.Location;
			//TPrequest = true;
			
			
		}
		
	}
	
	ClearArc();
	if(IsTPchecking)
	{
		//Trace Telepot Destination Function
		FPredictProjectilePathResult PredictResult;
		//may need fixed
		FPredictProjectilePathParams PredictParams = FPredictProjectilePathParams(0.0,TPDirection->GetWorldLocation(),TPDirection->GetForwardVector()*TPLaunchVelocity,2.0,EObjectTypeQuery::WorldStatic,this);
	
		bool TPcheck = PredictProjectilePath(GetWorld(),PredictParams,PredictResult);
		FVector ProjectedLocation;
		bool standPalce = ProjectPointToNavigation(PredictResult.HitResult.Location,ProjectedLocation,FVector(500.0,500.0,500.0));
		bool success = TPcheck and standPalce;
		//Trace Telepot Destination Function END
		IsTPValid = success;
		//sequence p1
		TPCylinder->SetVisibility(IsTPValid,true);
		FHitResult LandHitResult;
		FCollisionObjectQueryParams LandObjects = FCollisionObjectQueryParams(ECollisionChannel::WorldStatic);
		FCollisionQueryParams  Params;

		bool LandHit = GetWorld()->LineTraceSingleByObjectType(LandHitResult,ProjectedLocation,ProjectedLocation-FVector(0,0,-200),LandObjects,Params);
		if(LandHit)
		{
			TPCylinder->SetWorldLocation(LandHitResult.Location);
		}
		else
		{
			TPCylinder->SetWorldLocation(ProjectedLocation);
		}
		// sequence p2 is skiped
		// sequence p3 may be skipped if needed, create new bool
		//sequence p4 
		UpdateSpline(IsTPValid,PredictResult.PathData);
		UpdateEndpoint(IsTPValid,PredictResult.HitResult.Location);
	}
}

// Called to bind functionality to input
void AcVRPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//InputComponent->BindAction("GripLeft", IE_Pressed, this, &AcVRPlayerPawn::GripLeftHand_Pressed);
	InputComponent->BindAction("GripRight", IE_Pressed, this, &AcVRPlayerPawn::GripRightHand_Pressed);
	//InputComponent->BindAction("GripLeft", IE_Released, this, &AcVRPlayerPawn::GripLeftHand_Released);
	InputComponent->BindAction("GripRight", IE_Released, this, &AcVRPlayerPawn::GripRightHand_Released);
	//InputComponent->BindAction("return to menu(tmp)", IE_Released, this, &AcVRPlayerPawn::Return_to_main);
	//InputComponent->BindAction("unassigned left grip", IE_Pressed, this, );
	InputComponent->BindAction("TPprep", IE_Pressed, this, );
	//InputComponent->BindAction("unassigned left grip", IE_Released, this, );
	InputComponent->BindAction("TP", IE_Released, this, &AcVRPlayerPawn::TP_Player);
	InputComponent->BindAction("Swap Houses", IE_Released, this, &AcVRPlayerPawn::TP_Houses);
	//InputComponent->BindAction("Swap Houses", IE_Released, this, );
	//InputComponent->BindAxis("MoveForward", this, &AcVRPlayerPawn::ForwardMove);
	


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
	compVRCameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VR Camera Root"));
	compVRCameraRoot->SetupAttachment(rootComponent);
	compVRCameraRoot->SetRelativeLocationAndRotation(FVector::ZeroVector,FQuat::Identity);
	compVRCameraRoot->SetRelativeScale3D(FVector::OneVector);
 
	//Create a camera component and attach this to the camera root.
	compVRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("HMD Camera"));
	compVRCamera->SetupAttachment(compVRCameraRoot);
	compVRCamera->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
	compVRCamera->SetRelativeScale3D(FVector::OneVector);

	
	CreateHandController(compVRCameraRoot, "MC_Left", FXRMotionControllerBase::LeftHandSourceId);
	CreateHandController(compVRCameraRoot, "MC_Right",FXRMotionControllerBase::RightHandSourceId);
	
	
	//create mesh to indicate TP location for arrow parts
	TPEndPoint=CreateDefaultSubobject<UStaticMesh>(TEXT("ArcEndPoint"));
	TPEndPoint->SetupAttachment(rootComponent);
	//create a Cylinder to show a possible teleport location
	TPCylinder=CreateDefaultSubobject<UStaticMesh>(TEXT("TeleportCylinder"));
	TPCylinder->SetupAttachment(rootComponent);
	//create the parts of the TP indicator 
	TPRing=CreateDefaultSubobject<UStaticMesh>(TEXT("Ring"));
	TPRing->SetupAttachment(TPCylinder);
	
	TPArrow=CreateDefaultSubobject<UStaticMesh>(TEXT("Arrow"));
	TPArrow->SetupAttachment(TPCylinder);
	
	TPRoomScaleMesh=CreateDefaultSubobject<UStaticMesh>(TEXT("RoomScaleMesh"));
	TPRoomScaleMesh->SetupAttachment(TPArrow);
	
	

}

void AcVRPlayerPawn::CreateHandController(USceneComponent* a_compParent, FName a_strDisplayName, FName a_nameHandType)
{
	UMotionControllerComponent* compMotionController = CreateDefaultSubobject<UMotionControllerComponent>(a_strDisplayName);
	compMotionController->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
	
	if (a_nameHandType == FXRMotionControllerBase::LeftHandSourceId)
	{
		compMotionController->SetRelativeScale3D(FVector(1,1,-1));
		//SetWorldScale3D
		TPDirection=  CreateDefaultSubobject<UArrowComponent>(TEXT("Arc Direction"));
		TPDirection->SetupAttachment(compMotionController);
		TPDirection->SetArrowColor(FColor::Red);
		TPDirection->ArrowSize = 0.5;
		TPDirection->ArrowLength = 100;
		TPSpline=  CreateDefaultSubobject<USplineComponent>(TEXT("Arc Spline"));
		TPSpline->SetupAttachment(compMotionController);
		
	}
	else
	{
		compMotionController->SetRelativeScale3D(FVector::OneVector);
		//create a widget interaction to interact with the menu UI
		menuInteract =  CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("UI Interaction"));
		menuInteract->SetupAttachment(compMotionController);
		menuInteract->InteractionDistance = 500;
		menuInteract->PointerIndex=1.0;
	

	
	}
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
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> HandMeshObject(TEXT("SkeletalMesh'/Game/VirtualReality/Mannequin/Character/Mesh/MannequinHand_Right.MannequinHand_Right'"));
	//if (!HandMeshObject.Object)
	//{
		//UE_LOG(LogTemp, Error, TEXT("Could not load the default cube for hand mesh"));
		//return NULL;
	//}
	if (!refComponentHand)
	{
		//create the mesh component
		refComponentHand = CreateDefaultSubobject<USkeletalMeshComponent>(a_strDisplayName);
		//set the mesh to the component
		//refComponentHand->SetSkeletalMesh(HandMeshObject.Object,true);
	
 
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
	//static ConstructorHelpers::FObjectFinder<UClass> HandAnimBP(TEXT("AnimBlueprintGeneratedClass'/Game/VirtualReality/Mannequin/Animations/RightHand_AnimBP.RightHand_AnimBP_C'"));
	/*if (HandAnimBP.Succeeded())
	{
		a_refHand->AnimClass = HandAnimBP.Object;
		a_refHand->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		a_refHand->SetAnimInstanceClass(HandAnimBP.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not load the hand anim BP"));
	}*/
}



void AcVRPlayerPawn::GripLeftHand_Pressed_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Left Hand Grip Pressed"));
	//m_refLeftHandAnimBP->SetGripValue(1.0f);
	//if bool call targets clicked
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Purple, TEXT("click "));
	}
	//menuInteract->PressPointerKey(EKeys::LeftMouseButton);
	//menuInteract->PressAndReleaseKey(EKeys::LeftMouseButton);

}
void AcVRPlayerPawn::GripRightHand_Pressed_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Right Hand Grip Pressed"));
	//m_refRightHandAnimBP->SetGripValue(1.0f);
	
	menuInteract->PressPointerKey(EKeys::LeftMouseButton);


}
void AcVRPlayerPawn::GripLeftHand_Released_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Left Hand Grip Released"));
	//m_refLeftHandAnimBP->SetGripValue(0.0f);
	
	
	
}
void AcVRPlayerPawn::GripRightHand_Released_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Right Hand Grip Released"));
	//m_refRightHandAnimBP->SetGripValue(0.0f);
	if(IsHighlighting)
	{
		
		
		if(CurHighlighted)
		{
			CurHighlighted->OnActivate();
		}	
	}
	menuInteract->ReleasePointerKey(EKeys::LeftMouseButton);
}

void AcVRPlayerPawn::TP_Player_Implementation()
{
	
	if(TPrequest)
	{
		RootComponent->SetWorldLocation(TpLocation+FVector(0,0,96));
	}
}
void AcVRPlayerPawn::TP_Houses_Implementation()
{
	//UGameplayStatics::PlaySoundAtLocation(GetWorld(),'/Game/OtherAssets/MYmaterials/250129__tim-kahn__portal01.250129__tim-kahn__portal01',FVector(0, 0, 0));
	if (UGameplayStatics::GetCurrentLevelName(this) != "MainMenu1") 
	{
		if (inPuzzleHouse)
		{
			RootComponent->SetWorldLocation(RootComponent->GetComponentLocation() + DistanceBetweenHouses);
			inPuzzleHouse = false;
		}
		else
		{
			RootComponent->SetWorldLocation(RootComponent->GetComponentLocation() - DistanceBetweenHouses);
			inPuzzleHouse = true;
		}
	}
}

void AcVRPlayerPawn::Return_to_main_Implementation()
{
	//UGameplayStatics::OpenLevel(this, "MainMenu1");
}
void AcVRPlayerPawn::TP_Ready_Implementation()
{
	
	IsTPchecking=true;
	TPCylinder->SetVisibility(true,true)
}
void AcVRPlayerPawn::ClearArc()
{
	//SplineMeshs->DestroyComponent();
	SplineMeshs.Empty();
	TPSpline->ClearSplinePoints(true);
}
void AcVRPlayerPawn::UpdateSpline(bool haveValidLocation, TArray<FPredictProjectilePathPointData> SplinePoints)
{
	if(!haveValidLocation)
	{
		SplinePoints.Empty();
			
		SplinePoints.Add(FPredictProjectilePathPointData(TPDirection->GetWorldLocation(),FVector(0,0,0),0));
		SplinePoints.Add(FPredictProjectilePathPointData((TPDirection->GetWorldLocation()*20)+TPDirection->GetWorldLocation(),FVector(0,0,0),0)));
	}
		
	for (int i = 0; i < SplinePoints.Num(); i++) 
	{ 
		TPSpline->AddSplinePoint(SplinePoints[i].Location,true);
	}
	TPSpline->SetSplinePointType(SplinePoints.FindLast(SplinePoints.Last()),ESplinePointType::CurveClamped,true);
	for(int j =0;j<TPSpline->GetNumberOfSplinePoints()-2;j++)
	{
		USplineMeshComponent *s = ConstructObject<USplineMeshComponent>(USplineMeshComponent::StaticClass(), this);
		s->SetStaticMesh(Mesh);
		s->SetStartAndEnd(SplinePoints[j].Location, TPSpline->GetTangentAtSplinePoint(j,ESplineCoordinateSpace::Local), SplinePoints[j+1],TPSpline->GetTangentAtSplinePoint(j+1,ESplineCoordinateSpace::Local,true);
	}
}

void AcVRPlayerPawn::UpdateEndpoint(bool haveValidLocation, Vector NewLocation)
{
	TPEndPoint->SetVisibility(haveValidLocation and IsTPValid,false);
	TPEndPoint->SetWorldLocation(NewLocation,false,true);
	//TPArrow->SetWorldRotation();
}
