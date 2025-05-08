// Fill out your copyright notice in the Description page of Project Settings.
#include "PathfindingManager.h"
#include "Obstacle.h"
#include "AStarAIController.h"

void UPathfindingManager::Init(UWorld* world, UStaticMeshComponent* aimesh, UStaticMeshComponent* obstaclemesh) {
	UE_LOG(LogTemp, Warning, TEXT("MANAGER INIT"));

    World = world;

    // Generate grid map
    for (int y = 0; y < terrainLength; y++) {
        for (int x = 0; x < terrainWidth; x++) {
            if (rand() % 3 == 0) {
                AObstacle* obstacle = World->SpawnActor<AObstacle>(FVector(x,y,0) * cellSize, FRotator());
                obstacle->Init(obstaclemesh);
                obstacles.Push(obstacle);
                terrainTiles.Push(1);
            }
            else {
                terrainTiles.Push(0);
            }
        }
    }

    for (int y = 0; y < terrainLength; y++) {
        for (int x = 0; x < terrainWidth; x++) {
            if (terrainTiles[y * terrainWidth + x] == 0) {
                FVector pos(x * cellSize, y * cellSize, 0);
                aiController = World->SpawnActor<AAStarAIController>(pos, FRotator());
                aiController->Init(aimesh, 0);
                aiController->x = x;
                aiController->y = y;
                break;
            }
        }
        if (aiController) {
            break;
        }
    }
    initialized = true;
}

void UPathfindingManager::Update() {
    if (aiController->goalReached()) { 
        // Find random empty space on map

        int x = 0;
        int y = 0;
        do {
            x = rand() % terrainWidth;
            y = rand() % terrainLength;
        } while (terrainTiles[y * terrainWidth + x] > 0);
        

        FVector2f goal(x, y);
        FVector2f start(aiController->x, aiController->y);

        // Find path using the A* algorithm

        struct Entry
        {
            FVector2f pos;
            float cost;
            bool operator <(const Entry& b) const {
                return cost > b.cost;
            }
        } ;
        auto cmp = [](Entry left, Entry right) { return left.cost < right.cost; };
        
        TArray<Entry> frontier;
        frontier.Push(Entry{start, 0});
        TMap<FVector2f, FVector2f> came_from;
        TMap<FVector2f, float> cost_so_far;
        came_from.Add(start, FVector2f(-1, -1));
        cost_so_far.Add(start, 0);
        auto heuristic = [](FVector2f a, FVector2f b) { // use manhattan distance
            return abs(a.X - b.X) + abs(a.Y - b.Y);
        };
        
        TArray<FVector2f> offsets = { FVector2f(-1, 0), FVector2f(1, 0), FVector2f(0, -1), FVector2f(0, 1) };
        
        while (!frontier.IsEmpty()) {
            auto current = frontier.Last().pos;
            frontier.Pop();
            if (current == goal) {
                break;
            }
            TArray<FVector2f> neighbors;
            // find neighbors that are inbound

            for (auto offset : offsets) {
                auto neighbor = offset + current;
                if (neighbor.X < 0 || neighbor.X >= terrainWidth || neighbor.Y < 0 || neighbor.Y >= terrainLength) {
                    continue;
                }
                if (terrainTiles[((int)neighbor.X + (int)neighbor.Y * terrainWidth)] > 0) {
                    continue;
                }
                neighbors.Push(neighbor);
            }
            for (auto next : neighbors) {
                auto new_cost = cost_so_far[current] + 1;
                if (!cost_so_far.Contains(next) || new_cost < cost_so_far[next]) {
                    cost_so_far.FindOrAdd(next, new_cost);
                    auto priority = new_cost + heuristic(goal, next);
                    frontier.Push(Entry{ next, priority });
                    frontier.Sort();
                    came_from.FindOrAdd(next, current);
                }
            }
        }
        
        // Quit if goal not pathable
        if (!came_from.Contains(goal)) {
            UE_LOG(LogTemp, Warning, TEXT("GOAL NOT FOUND"));
            return;
        }
        UE_LOG(LogTemp, Warning, TEXT("GOAL FOUND"));
        TArray<FVector> path;
        auto current = goal;
        while (current != start) {
            path.Push(FVector(current.X, current.Y, 0) * cellSize);
            UE_LOG(LogTemp, Warning, TEXT("%f, %f"), current.X, current.Y);
            current = came_from[current];
        }
        aiController->x = (int)goal.X;
        aiController->y = (int)goal.Y;
        UE_LOG(LogTemp, Warning, TEXT("%d"), path.Num());
        aiController->setPath(path);
    }
}