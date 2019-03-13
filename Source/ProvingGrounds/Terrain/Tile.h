// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class PROVINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	UFUNCTION(BlueprintCallable, Category = "Setup" )
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int Min = 1, int Max = 1, float Radius = 500, float MinScale = 1.f, float MaxScale = 1.f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	bool CanSpawnAtLocation(FVector Location, float Radius);
	
	bool FindEmptyLocation(FVector& OutLocation, float Radius);
	
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector RandomSpotInTile, float Rotation, float Scale);
};
