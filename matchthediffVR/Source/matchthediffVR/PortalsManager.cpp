// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalsManager.h"

#include <dsound.h>

#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortalsManager::APortalsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!PuzzlePortal)
	{
		// Use a sphere as a simple collision representation.
		PuzzlePortal = CreateDefaultSubobject<UBoxComponent>(TEXT("PuzzlePortal"));
		PuzzlePortal->OnComponentBeginOverlap.AddDynamic(this, &APortalsManager::OnOverlapPuzzle);
		PuzzlePortal->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
		PuzzlePortal->CanCharacterStepUpOn = ECB_No;
		
	}
	if (!SolutionPortal)
	{
		// Use a sphere as a simple collision representation.
		SolutionPortal = CreateDefaultSubobject<UBoxComponent>(TEXT("SolutionPortal"));
		SolutionPortal->OnComponentBeginOverlap.AddDynamic(this, &APortalsManager::OnOverlapSolution);
		SolutionPortal->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
		SolutionPortal->CanCharacterStepUpOn = ECB_No;
		
	}
}

void APortalsManager::OnOverlapPuzzle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Player = Cast<ACharacter>(OtherActor);
	if (Player)
	{
		Player->SetActorLocation(GetCurrentStagTeleportLocation(true));
		//Player->SetActorRotation(Player->GetActorRotation()*180);
		if(TPSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), TPSound, PuzzlePortal->GetComponentLocation());
		}
	}
	
}
void APortalsManager::OnOverlapSolution(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Player = Cast<ACharacter>(OtherActor);
	if (Player)
	{
		Player->SetActorLocation(GetCurrentStagTeleportLocation(false));
		//Player->SetActorRotation(Player->GetActorRotation()*180);
		if(TPSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), TPSound, PuzzlePortal->GetComponentLocation());
		}
	}
}

void APortalsManager::UpdatePortalLocations(int StageNumber)
{
	switch (StageNumber)
	{
		case 1:
			PuzzlePortal->SetWorldLocation(Stage1Puzzle);
			SolutionPortal->SetWorldLocation(Stage1Solution);
			CurrentStage = StageNumber;
			break;
		case 2:
			PuzzlePortal->SetWorldLocation(Stage2Puzzle);
			SolutionPortal->SetWorldLocation(Stage2Solution);
			CurrentStage = StageNumber;
			break;
		case 3:
			PuzzlePortal->SetWorldLocation(Stage3Puzzle);
			SolutionPortal->SetWorldLocation(Stage3Solution);
			CurrentStage = StageNumber;
			break;
		case 4:
			PuzzlePortal->SetWorldLocation(Stage4Puzzle);
			SolutionPortal->SetWorldLocation(Stage4Solution);
			CurrentStage = StageNumber;
			break;
		default:
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1,1.0,FColor::Red,FString("Not An Existing stage"));
			}
		break;
	}
	
}

// Called when the game starts or when spawned
void APortalsManager::BeginPlay()
{
	Super::BeginPlay();
	UpdatePortalLocations(1);
	
	
}
int APortalsManager::GetCurrentStage()
{
	return CurrentStage;
}

FVector APortalsManager::GetCurrentStagTeleportLocation(bool isPuzzle)
{
	switch (GetCurrentStage())
	{
	case 1:
		
		if(!isPuzzle)
		{
			return Stage1Puzzle+TPOffset;
		}
		return Stage1Solution+TPOffset;
	case 2:
		if(!isPuzzle)
		{
			return Stage2Puzzle+TPOffset;
		}
		return Stage2Solution+TPOffset;
	case 3:
		if(!isPuzzle)
		{
			return Stage3Puzzle+TPOffset;
		}
		return Stage3Solution+TPOffset;
	case 4:
		if(!isPuzzle)
		{
			return Stage4Puzzle-TPOffset;
		}
		return Stage4Solution-TPOffset;
	default:
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,1.0,FColor::Red,FString("Not An Existing stage"));
		}
		return FVector(0,0,0);
	}
		
}

// Called every frame
void APortalsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

