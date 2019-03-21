// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProvingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"


/**
 * 
 */
UCLASS()
class PROVINGGROUNDS_API AInfiniteTerrainGameMode : public AProvingGroundsGameMode
{
	GENERATED_BODY()

public:
	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "NavBounds Pool")
	void PopulateBoundsVolumePool();

public:

	void AddPool(class ANavMeshBoundsVolume *VolumeToAdd);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BoundsPool")
	class UActorPool* NavMeshBoundsVolumePool;

};
