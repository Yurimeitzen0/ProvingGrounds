// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


USTRUCT(BlueprintType)
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Struct")
	FVector Location;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Struct")
	float Rotation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Struct")
	float Scale;
};


UCLASS()
class PROVINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	UFUNCTION(BlueprintCallable, Category = "Spawning" )
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int Min = 1, int Max = 1, float Radius = 500, float MinScale = 1.f, float MaxScale = 1.f);
	
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceAiPawns(TSubclassOf<APawn> ToSpawn, int Min = 1, int Max = 1, float Radius = 500);


	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(class UActorPool* Pool);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason )override;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinBox;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxBox;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundsOffset;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	bool CanSpawnAtLocation(FVector Location, float Radius);
	
	bool FindEmptyLocation(FVector& OutLocation, float Radius);
	
	void PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition);

	void PlaceActor(TSubclassOf<APawn> ToSpawn, const FSpawnPosition &SpawnPosition);

	void PositionNavMeshBoundsVolume();

	class UActorPool* Pool;

	AActor* NavMeshBoundsVolume;

	template<class Generate>
	void RandomlyPlaceActors(TSubclassOf<Generate> ToSpawn, int Min = 1, int Max = 1, float Radius = 500, float MinScale = 1.f, float MaxScale = 1.f);

	
};


