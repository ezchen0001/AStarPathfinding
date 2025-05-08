// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "PathfindingManager.h"
#include "PathfindingGameModeBase.generated.h"

UCLASS()
class PATHFINDING_API APathfindingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	APathfindingGameModeBase();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* AIMesh;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ObstacleMesh;

	UPathfindingManager* Manager;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};