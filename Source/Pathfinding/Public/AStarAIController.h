// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AStarAIController.generated.h"

UCLASS()
class PATHFINDING_API AAStarAIController : public AActor
{
	GENERATED_BODY()

public:
	AAStarAIController();
	void Init(UStaticMeshComponent* mesh, int id);
	UStaticMeshComponent* Mesh;
	TArray<FVector> queue;
	float timeElapsed = 0;
	float stepDuration = 0.25;
	int x = 0;
	int y = 0;
protected:
	virtual void BeginPlay() override;

public:
	bool goalReached();
	void setPath(TArray<FVector> queue);
	virtual void Tick(float DeltaTime) override;
};