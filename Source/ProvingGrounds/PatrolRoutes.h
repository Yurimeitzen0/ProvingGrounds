// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoutes.generated.h"

/**
* A component containing the patrol points references.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROVINGGROUNDS_API UPatrolRoutes : public UActorComponent
{
	GENERATED_BODY()

public:	
	TArray<AActor*> GetPatrolPoints() const;
private:
	UPROPERTY(EditInstanceOnly, Category = "PatrolRoute")
		TArray <AActor*> PatrolPointsC;

};
