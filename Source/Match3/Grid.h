// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <vector>
#include <array>
#include "ResponseEventSubscription.h"

#include "Grid.generated.h"

class ATile;
class UGameController;

USTRUCT(BlueprintType)
struct MATCH3_API FTileDropdownData
{
	GENERATED_BODY()

public:
	FTileDropdownData() {};
	FTileDropdownData(ATile* tile, FVector startingPosition, FVector destinationPosition) : Tile(tile), StartingPosition(startingPosition), DestinationPosition(destinationPosition) {};

	UPROPERTY(BlueprintReadWrite)
	ATile* Tile;

	UPROPERTY(BlueprintReadWrite)
	FVector StartingPosition;
	
	UPROPERTY(BlueprintReadWrite)
	FVector DestinationPosition;
};

UCLASS()
class MATCH3_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();
	
	void Initialize(UGameController* gameController);

	void CreateBoard(std::array<std::array<int, 10>, 10> board);

	void OnTileClicked(ATile* tile);

	UFUNCTION(BlueprintImplementableEvent)
	void SwapTiles(ATile* first, ATile* second, bool isMoveCombo);

	UFUNCTION(BlueprintImplementableEvent)
	void DropdownTiles(const TArray<FTileDropdownData>& tiles);

	UFUNCTION(BlueprintImplementableEvent)
	void EnlargeComboTiles(const TArray<ATile*>& tiles);

	UFUNCTION(BlueprintCallable)
	void OnSwapTilesFinished(bool isMoveCombo);

	UFUNCTION(BlueprintCallable)
	void OnDropdownFinished();

	UFUNCTION(BlueprintCallable)
	void OnEnlargeTilesFinished();

public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ATile> TileClass;

	UPROPERTY(EditAnywhere)
		FRotator Rotation;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

private:
	void MoveTiles(ATile* firstTile, ATile* secondTile);
	void MarkTilesForDestruction();
	void BreakCombos();
	void StartDropdown();
	void OnCombo();

	void OnOpponentTileMove(JSONObjectNode::Ptr response);
	void OnNewTilesReceived(JSONObjectNode::Ptr response);
	void OnEndTurn(JSONObjectNode::Ptr response);

	void SpawnNewTilesForDropdown(std::array<std::vector<int>, 10> newTileTypes);

private:
	std::vector<ATile*> _tiles;

	bool _isTileSelected;
	ATile* _selectedTile;

	UGameController* _gameController;

	std::array<std::array<int, 10>, 10> _dropdownTable;
	std::array<std::array<bool, 10>, 10> _destroyTableInfo;
	std::array<int, 10> _dropdownInfoArray;

	TArray<ATile*> _destroyData;
	TArray<FTileDropdownData> _dropdownData;

	ResponseEventSubscription::Ptr _opponentTileMoveSubscription;
	ResponseEventSubscription::Ptr _newTilesGeneratedSubscription;
	ResponseEventSubscription::Ptr _onEndTurnSubscription;
};

