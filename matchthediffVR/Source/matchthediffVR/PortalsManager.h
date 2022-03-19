// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalsManager.generated.h"

class UBoxComponent;
UCLASS()
class MATCHTHEDIFFVR_API APortalsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalsManager();
	/**portal for Puzzle house*/
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UBoxComponent* PuzzlePortal;
	/**portal for Solution house*/
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UBoxComponent* SolutionPortal;
	
	UFUNCTION()
	void OnOverlapPuzzle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapSolution(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/*Changes the Portal Location Based on what the current stage is
	 * @param StageNumber is the stage we are changing it to( must fit within the existing number of stages
	 */
	UFUNCTION()
	void UpdatePortalLocations(int StageNumber);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/**Stage 1 puzzle Portal location, MUST be set in blueprints*/
	UPROPERTY(EditAnywhere, Category = "Portal Locations", meta= (AllowProtectedAccess= "true"))
	FVector Stage1Puzzle;
	/**Stage 1 solution Portal location, MUST be set in blueprints*/
	UPROPERTY(EditAnywhere, Category = "Portal Locations", meta= (AllowProtectedAccess= "true"))
	FVector Stage1Solution;
	/**Stage 2 puzzle Portal location, MUST be set in blueprints*/
	UPROPERTY(EditAnywhere, Category = "Portal Locations", meta= (AllowProtectedAccess= "true"))
	FVector Stage2Puzzle;
	/**Stage 2 solution Portal location, MUST be set in blueprints*/
	UPROPERTY(EditAnywhere, Category = "Portal Locations", meta= (AllowProtectedAccess= "true"))
	FVector Stage2Solution;
	/**Stage 3 puzzle Portal location, MUST be set in blueprints*/
	UPROPERTY(EditAnywhere, Category = "Portal Locations", meta= (AllowProtectedAccess= "true"))
	FVector Stage3Puzzle;
	/**Stage 3 solution Portal location, MUST be set in blueprints*/
	UPROPERTY(EditAnywhere, Category = "Portal Locations", meta= (AllowProtectedAccess= "true"))
	FVector Stage3Solution;
	/**Stage 4 puzzle Portal location, MUST be set in blueprints*/
	UPROPERTY(EditAnywhere, Category = "Portal Locations", meta= (AllowProtectedAccess= "true"))
	FVector Stage4Puzzle;
	/**Stage 4 solution Portal location, MUST be set in blueprints*/
	UPROPERTY(EditAnywhere, Category = "Portal Locations", meta= (AllowProtectedAccess= "true"))
	FVector Stage4Solution;

	UPROPERTY(EditAnywhere, Category = "Portal Locations", meta= (AllowProtectedAccess= "true"))
	FVector TPOffset;
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	int CurrentStage = 1;
	UFUNCTION()
	int GetCurrentStage();
	UFUNCTION()
	FVector GetCurrentStagTeleportLocation(bool isPuzzle);
	/**Teleporting sound*/ 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other stuff", meta = (AllowProtectedAccess = "true"))
	USoundBase* TPSound;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};


