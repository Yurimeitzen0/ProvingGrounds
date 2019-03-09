// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Runtime/Engine/Classes/Engine/World.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int Min, int Max)
{
	int RandomSpawn = FMath::RandRange(Min, Max);
	for (int i = 0; i < RandomSpawn; i++)
	{

		auto RandomSpotInTile = FMath::RandPointInBox(FBox(FVector(0, -2000, 0), FVector(4000, 2000, 0	)));
		AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
		Spawned->SetActorRelativeLocation(RandomSpotInTile);
		Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, "false");
	}
	
	
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

