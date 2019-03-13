// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int Min, int Max, float Radius, float MinScale, float MaxScale)
{
	int RandomSpawn = FMath::RandRange(Min, Max);
	for (int i = 0; i < RandomSpawn; i++)
	{
		FVector OutLocation; 
		float RandomScale = FMath::FRandRange(MinScale, MaxScale);
		bool Found = FindEmptyLocation(OutLocation, Radius*RandomScale);
		
		if (Found)
		{
			float RandomRotation = FMath::FRandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, OutLocation, RandomRotation, RandomScale);
		}
		
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

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult OutHit;
	Location = ActorToWorld().TransformPosition(Location); 
	bool HasHit = GetWorld()->SweepSingleByChannel(OutHit, Location, Location, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	/*FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), Location,0, Radius, FQuat::Identity, ResultColor, true, 30);*/
	return !HasHit;
}

bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius)
{
	auto RandomLocation = FMath::RandPointInBox(FBox(FVector(0, -2000, 0), FVector(4000, 2000, 0)));
	if (CanSpawnAtLocation(RandomLocation, Radius))
	{
		OutLocation = RandomLocation;
		return true;
	}
	else
	{
		return FindEmptyLocation(OutLocation, Radius);
	}
	
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector RandomSpotInTile, float Rotation, float Scale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(RandomSpotInTile);
	Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, "false");
	Spawned->SetActorRotation(FRotator(0, Rotation, 0));
	Spawned->SetActorScale3D(FVector(Scale));
	
}

