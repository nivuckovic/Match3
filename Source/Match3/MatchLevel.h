// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatchLevel.generated.h"

class AGrid;
class UGameController;

UCLASS()
class MATCH3_API AMatchLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMatchLevel();

	void SetGameController(UGameController* gameController);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGrid> GridClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BoardClass;

	AGrid* Grid;
	AActor* Board;

private:
	UGameController* _gameController;
};
