// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarAIController.h"

AAStarAIController::AAStarAIController() {
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AStarAIControllerMesh"));
	RootComponent = Mesh;
}

void AAStarAIController::BeginPlay() {
	Super::BeginPlay();
}

void AAStarAIController::Init(UStaticMeshComponent* mesh, int id) {
	UE_LOG(LogTemp, Warning, TEXT("AStarAIController initialized."));
	Mesh->SetStaticMesh(mesh->GetStaticMesh());
}

bool AAStarAIController::goalReached()
{
	return queue.IsEmpty() && timeElapsed > 2;
}

void AAStarAIController::setPath(TArray<FVector> newQueue)
{
	timeElapsed = 0;
	queue = newQueue;
}



void AAStarAIController::Tick(float DeltaTime) { // Move to next position in path and wait a delay
	Super::Tick(DeltaTime);
	timeElapsed += DeltaTime;
	if (queue.IsEmpty()) {
		return;
	}

	SetActorLocation((GetActorLocation() + queue.Top()) * 0.5);
	if (timeElapsed > stepDuration) {
		timeElapsed = 0;
		queue.Pop();
	}
}