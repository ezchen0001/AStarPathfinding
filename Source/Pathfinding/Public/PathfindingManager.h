#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "PathfindingManager.generated.h"

UCLASS()
class PATHFINDING_API UPathfindingManager : public UObject
{

public:
	GENERATED_BODY()

	void Init(UWorld* world, UStaticMeshComponent* aimesh, UStaticMeshComponent* obstaclemesh);
	void Update();

private:
	UWorld* World;
	bool initialized;

	int terrainWidth = 10;
	int terrainLength = 10;
	const float cellSize = 200;

	TArray<int> terrainTiles = {};
	TArray<class AObstacle*> obstacles;
	class AAStarAIController* aiController = nullptr;
};