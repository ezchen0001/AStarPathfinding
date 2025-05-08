// Fill out your copyright notice in the Description page of Project Settings.

#include "PathfindingGameModeBase.h"

APathfindingGameModeBase::APathfindingGameModeBase() {
    AIMesh = CreateDefaultSubobject<UStaticMeshComponent>("AIMesh");
    ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>("ObstacleMesh");
    PrimaryActorTick.bCanEverTick = true;
}
void APathfindingGameModeBase::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("GAMEMODE BEGINPLAY()"));
    Manager = NewObject<UPathfindingManager>();
    Manager->Init(GetWorld(), AIMesh, ObstacleMesh);
}

void APathfindingGameModeBase::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    Manager->Update();
};