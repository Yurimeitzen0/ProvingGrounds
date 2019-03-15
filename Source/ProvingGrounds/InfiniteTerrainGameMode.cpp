// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InfiniteTerrainGameMode.h"
#include "EngineUtils.h"
#include "Navmesh/NavMeshBoundsVolume.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld(), ANavMeshBoundsVolume::StaticClass());

	while (VolumeIterator)
	{
		AddPool(*VolumeIterator);
		++VolumeIterator;
	}

}

void AInfiniteTerrainGameMode::AddPool(ANavMeshBoundsVolume *VolumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("NavMeshFound %s"), *VolumeToAdd->GetName());
}
