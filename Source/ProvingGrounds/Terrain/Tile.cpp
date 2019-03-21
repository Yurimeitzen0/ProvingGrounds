// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "NavigationSystem.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MinBox = FVector(0, -2000, 0);
	MaxBox = FVector(4000, 2000, 0);
	NavigationBoundsOffset = FVector(2000, 0, 0);
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int Min, int Max, float Radius, float MinScale, float MaxScale)
{
	TArray<FSpawnPosition> SpawnPositions = RandomSpawnPositions(Min, Max, MinScale, MaxScale, Radius);
	for (FSpawnPosition SpawnPosition : SpawnPositions)
	{
		PlaceActor(ToSpawn, SpawnPosition);
	}
	
	
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, "false");
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));

}

void ATile::PlaceAiPawns(TSubclassOf<APawn> ToSpawn, int Min, int Max, float Radius)
{
	TArray<FSpawnPosition> SpawnPositions = RandomSpawnPositions(Min, Max, 1, 1, Radius);
	for (FSpawnPosition SpawnPosition : SpawnPositions)
	{
		PlaceAiPawn(ToSpawn, SpawnPosition);
	}
	
}

void ATile::PlaceAiPawn(TSubclassOf<APawn> ToSpawn, const FSpawnPosition &SpawnPosition)
{
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, "false");
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	Spawned->SpawnDefaultController();
	Spawned->Tags.Add(FName("Enemy"));
}


TArray<FSpawnPosition> ATile::RandomSpawnPositions(int Min, int Max, float MinScale, float MaxScale, float Radius)
{
	TArray<FSpawnPosition> SpawnPositions;
	int RandomSpawn = FMath::RandRange(Min, Max);
	for (int i = 0; i < RandomSpawn; i++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::FRandRange(MinScale, MaxScale);
		bool Found = FindEmptyLocation(SpawnPosition.Location, Radius*SpawnPosition.Scale);

		if (Found)
		{
			SpawnPosition.Rotation = FMath::FRandRange(-180.f, 180.f);
			SpawnPositions.Add(SpawnPosition);

		}

	}
	return SpawnPositions;
}

void ATile::SetPool(UActorPool * InPool)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] SettingPool [%s]"), *(this->GetName()), *(InPool->GetName()));

	Pool = InPool; 

	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();

	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] :Not enough actors in pool"), *GetName());
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("[%s] Checked out: [%s]"), *GetName(), *NavMeshBoundsVolume->GetName());
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	UNavigationSystemV1::GetNavigationSystem(GetWorld())->Build();
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();


}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	Pool->Return(NavMeshBoundsVolume);
	
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
	auto RandomLocation = FMath::RandPointInBox(FBox(MinBox, MaxBox));
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




