// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class PATHFINDING_API AObstacle : public AActor
{
	GENERATED_BODY()

public:
	AObstacle();
	void Init(UStaticMeshComponent* mesh);
	UStaticMeshComponent* Mesh;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};