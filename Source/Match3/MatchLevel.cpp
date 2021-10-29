// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchLevel.h"

#include "Grid.h"
#include "MatchController.h"
#include "GameController.h"

// Sets default values
AMatchLevel::AMatchLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AMatchLevel::SetGameController(UGameController* gameController)
{
	_gameController = gameController;
}

// Called when the game starts or when spawned
void AMatchLevel::BeginPlay()
{
	Super::BeginPlay();

	FVector boardPosition(0, 0, 0);
	FRotator boardRotation(0, 0, 0);

	AActor* boardActor = GetWorld()->SpawnActor(BoardClass, &boardPosition, &boardRotation);
	
	boardActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);


	FVector position(0, 0, 0);
	FRotator rotation(0, 0, 0);

	FTransform transform;
	transform.SetTranslation(position);
	transform.SetRotation(FQuat(rotation));

	Grid = GetWorld()->SpawnActorDeferred<AGrid>(GridClass, transform, this);
	Grid->Initialize(_gameController);
	Grid->FinishSpawning(transform);
	Grid->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	Grid->CreateBoard(_gameController->Match->CurrentMatchState->Board);

}
