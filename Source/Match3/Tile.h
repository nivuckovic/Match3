// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"

#include "PaperSprite.h"

#include "Tile.generated.h"

class AGrid;

UCLASS()
class MATCH3_API ATile : public APaperSpriteActor
{
	GENERATED_BODY()
public:
	void Initialize(AGrid* grid, FVector boardPosition, int tileType);

	void SetTileSprite(int tileType);

	UFUNCTION(BlueprintCallable)
	void OnTileClicked();

	UFUNCTION(BlueprintCallable)
	void MoveTile(FVector newLocation);

	void Select();
	void Deselect();

	int GetType();

	void SetNewBoardPosition(FVector newBoardPosition);
	FVector GetBoardPosition();

public:
	UPROPERTY(EditDefaultsOnly)
	UPaperSprite* CheeseSprite;

	UPROPERTY(EditDefaultsOnly)
	UPaperSprite* DoughSprite;
	
	UPROPERTY(EditDefaultsOnly)
	UPaperSprite* HamSprite;
	
	UPROPERTY(EditDefaultsOnly)
	UPaperSprite* MushroomSprite;
	
	UPROPERTY(EditDefaultsOnly)
	UPaperSprite* TomatoSprite;

private:
	AGrid* _grid;

	FVector _boardPosition;

	int _type;
};
