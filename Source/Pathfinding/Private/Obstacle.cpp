// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

AObstacle::AObstacle() {
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	RootComponent = Mesh;
}

void AObstacle::BeginPlay() {
	Super::BeginPlay();
}

void AObstacle::Init(UStaticMeshComponent* mesh) {
	UE_LOG(LogTemp, Warning, TEXT("Obstacle initialized."));
	Mesh->SetStaticMesh(mesh->GetStaticMesh());
}

void AObstacle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}