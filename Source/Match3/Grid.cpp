// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

#include "Tile.h"
#include "GameController.h"
#include "MatchController.h"
#include "EventQueue.h"
#include "GameEvents.h"
#include <vector>
#include <algorithm>

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AGrid::Initialize(UGameController* gameController)
{
	_gameController = gameController;

	_opponentTileMoveSubscription = EventQueue::SubscribeToResponseEvent(ResponseType::OpponentMoveTile, std::bind(&AGrid::OnOpponentTileMove, this, std::placeholders::_1));
	_newTilesGeneratedSubscription = EventQueue::SubscribeToResponseEvent(ResponseType::NewTilesGenerated, std::bind(&AGrid::OnNewTilesReceived, this, std::placeholders::_1));
	_onEndTurnSubscription = EventQueue::SubscribeToResponseEvent(ResponseType::EndTurn, std::bind(&AGrid::OnEndTurn, this, std::placeholders::_1));
}

void AGrid::CreateBoard(std::array<std::array<int, 10>, 10> board)
{
	FRotator rotation(0, 0, 0);
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			FVector position(-75.5 + 752 - i * 151, +75.5 + -752 + j * 151, 50);

			ATile* tile = Cast<ATile>(GetWorld()->SpawnActor(TileClass, &position, &Rotation));
			tile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			tile->Initialize(this, FVector(i, j, 0), board[i][j]);

			_tiles.push_back(tile);
		}
	}
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
}

void AGrid::BeginDestroy()
{
	Super::BeginDestroy();

	if(_opponentTileMoveSubscription.get() != nullptr)
		EventQueue::UnsubscribeFromResponseEvent(_opponentTileMoveSubscription);
	if(_newTilesGeneratedSubscription.get() != nullptr)
		EventQueue::UnsubscribeFromResponseEvent(_newTilesGeneratedSubscription);
	if (_onEndTurnSubscription.get() != nullptr)
		EventQueue::UnsubscribeFromResponseEvent(_onEndTurnSubscription);
}

void AGrid::OnTileClicked(ATile* clickedTile)
{
	if (!_gameController->Match->IsYourTurn())
		return;

	if (_isTileSelected)
	{
		FVector firstPosition = clickedTile->GetBoardPosition();
		FVector secondPosition = _selectedTile->GetBoardPosition();

		int xAxisDistance = std::abs(firstPosition.X - secondPosition.X);
		int yAxisDistance = std::abs(firstPosition.Y - secondPosition.Y);

		// Is move valid
		if (clickedTile != _selectedTile && (xAxisDistance + yAxisDistance == 1))
		{
			ATile* alreadySelectedTile = _selectedTile;
			EventQueue::CallEvent(std::make_shared<TileMoveEvent>(firstPosition.X, firstPosition.Y, secondPosition.X, secondPosition.Y,
				[this, clickedTile, alreadySelectedTile](JSONObjectNode::Ptr) {
				this->MoveTiles(clickedTile, alreadySelectedTile);
			}));
		}

		_selectedTile->Deselect();

		_selectedTile = nullptr;
		_isTileSelected = false;
	}
	else
	{
		clickedTile->Select();

		_selectedTile = clickedTile;
		_isTileSelected = true;
	}
}

void AGrid::OnOpponentTileMove(JSONObjectNode::Ptr response)
{
	JSONObjectNode::Ptr data = response->GetValue<JSONObjectNode::Ptr>("data");
	int firstX = data->GetValue<int>("firstX");
	int firstY = data->GetValue<int>("firstY");
	int secondX = data->GetValue<int>("secondX");
	int secondY = data->GetValue<int>("secondY");

	ATile* firstTile = *std::find_if(_tiles.begin(), _tiles.end(), [firstX, firstY](ATile* tile) {
		return (tile->GetBoardPosition().X == firstX) && (tile->GetBoardPosition().Y == firstY);
	});

	ATile* secondTile = *std::find_if(_tiles.begin(), _tiles.end(), [secondX, secondY](ATile* tile) {
		return (tile->GetBoardPosition().X == secondX) && (tile->GetBoardPosition().Y == secondY);
	});

	MoveTiles(firstTile, secondTile);	
}

void AGrid::MoveTiles(ATile* firstTile, ATile* secondTile)
{
	bool isCombo = _gameController->Match->WillItBeComboAfterSwap(firstTile->GetBoardPosition(), secondTile->GetBoardPosition(), _destroyTableInfo);
	if (isCombo)
	{
		std::swap(_gameController->Match->CurrentMatchState->Board[firstTile->GetBoardPosition().X][firstTile->GetBoardPosition().Y], _gameController->Match->CurrentMatchState->Board[secondTile->GetBoardPosition().X][secondTile->GetBoardPosition().Y]);

		FVector tempPosition = firstTile->GetBoardPosition();
		firstTile->SetNewBoardPosition(secondTile->GetBoardPosition());
		secondTile->SetNewBoardPosition(tempPosition);
	}

	SwapTiles(firstTile, secondTile, isCombo);
}

void AGrid::OnSwapTilesFinished(bool isMoveCombo)
{
	if (isMoveCombo)
	{
		MarkTilesForDestruction();
		EnlargeComboTiles(_destroyData);
	}
}

void AGrid::MarkTilesForDestruction()
{
	_destroyData = TArray<ATile*>();

	for (ATile* tile : _tiles)
	{
		int x = tile->GetBoardPosition().X;
		int y = tile->GetBoardPosition().Y;

		if (_destroyTableInfo[x][y])
		{
			_destroyData.Add(tile);
		}
	}
}

void AGrid::OnEnlargeTilesFinished()
{
	OnCombo();
}

void AGrid::OnCombo()
{
	BreakCombos();
	_dropdownInfoArray = _gameController->Match->CalculateDropdownCount(_destroyTableInfo);

	if (_gameController->Match->IsYourTurn()) {
		std::vector<int> dropdownInfo(std::begin(_dropdownInfoArray), std::end(_dropdownInfoArray));
		EventQueue::CallEvent(std::make_shared<GenerateNewTilesEvent>(dropdownInfo, [this](JSONObjectNode::Ptr response) {
			this->OnNewTilesReceived(response);
		}));
	}
}

void AGrid::BreakCombos()
{
	for (ATile* tile : _destroyData)
	{
		int x = tile->GetBoardPosition().X;
		int y = tile->GetBoardPosition().Y;

		std::vector<ATile*>::iterator it = std::find_if(_tiles.begin(), _tiles.end(), [x, y](ATile* tile)
		{
			return (x == tile->GetBoardPosition().X) && (y == tile->GetBoardPosition().Y);
		});

		if (it != _tiles.end())
		{
			(*it)->Destroy();
			_tiles.erase(it);
		}
	}
}

void AGrid::OnNewTilesReceived(JSONObjectNode::Ptr response)
{
	JSONObjectNode::Ptr data = response->GetValue<JSONObjectNode::Ptr>("data");
	std::vector<int> newTileTypes = data->GetValue<std::vector<int>>("newTiles");

	// Create data from response vector
	std::array<std::vector<int>, 10> newGeneratedTiles;
	int pos = 0;
	for (int column = 0; column < 10; ++column)
	{
		int count = _dropdownInfoArray[column];
 
		if(count > 0)
			newGeneratedTiles[column].insert(newGeneratedTiles[column].begin(), newTileTypes.begin() + pos, newTileTypes.begin() + pos + count);

		pos += count;
	}

	SpawnNewTilesForDropdown(newGeneratedTiles);
	StartDropdown();
}

void AGrid::SpawnNewTilesForDropdown(std::array<std::vector<int>, 10> newTileTypes)
{
	// FVector position(-75.5 + 752 - i * 151, +75.5 + -752 + j * 151, 50);

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < newTileTypes[i].size(); ++j)
		{
			UE_LOG(LogTemp, Warning, TEXT("%d"), newTileTypes[i][j]);
		}

		UE_LOG(LogTemp, Warning, TEXT(""));
	}

	FRotator rotation(0, 0, 0);
	for (int column = 0; column < 10; ++column)
	{
		for (int row = 0; row < _dropdownInfoArray[column]; ++row)
		{
			FVector position(-75.5 + 752 + (row + 1) * 151, 75.5 - 752 + column * 151, 50);

			ATile* tile = Cast<ATile>(GetWorld()->SpawnActor(TileClass, &position, &Rotation));
			tile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			tile->Initialize(this, FVector(-(row + 1), column, 0), newTileTypes[column][row]);

			_tiles.push_back(tile);
		}
	}
}

void AGrid::StartDropdown()
{
	_dropdownData = TArray<FTileDropdownData>();

	_dropdownTable = _gameController->Match->CalculateDropdownTable(_destroyTableInfo);

	// Calculate dropdown destinations
	std::for_each(_tiles.begin(), _tiles.end(), [this](ATile* tile)
	{
		FTileDropdownData data;

		data.Tile = tile;
		data.StartingPosition = tile->GetActorLocation();

		FVector destinationPosition = tile->GetActorLocation();
		if (tile->GetBoardPosition().X < 0)
		{
			destinationPosition.X -= _dropdownInfoArray[tile->GetBoardPosition().Y] * 151;
		}
		else if (_dropdownTable[tile->GetBoardPosition().X][tile->GetBoardPosition().Y] > 0)
		{
			destinationPosition.X -= _dropdownTable[tile->GetBoardPosition().X][tile->GetBoardPosition().Y] * 151;
		}

		data.DestinationPosition = destinationPosition;

		_dropdownData.Add(data);
	});

	DropdownTiles(_dropdownData);
}

void AGrid::OnDropdownFinished()
{
	// Update board
	std::for_each(_tiles.begin(), _tiles.end(), [this](ATile* tile)
	{
		// updateaj tablicu (mozda posalji na server), ponavljaj dok ima comba, zavrsi turn

		FVector boardPosition = tile->GetBoardPosition();
		// Set correct position for new dropdown tiles
		if (boardPosition.X < 0)
		{
			tile->SetNewBoardPosition(FVector(_dropdownInfoArray[boardPosition.Y] + boardPosition.X, boardPosition.Y, 0));
			boardPosition.X = _dropdownInfoArray[boardPosition.Y] + boardPosition.X;
		}
		else
		{
			tile->SetNewBoardPosition(FVector(boardPosition.X + _dropdownTable[boardPosition.X][boardPosition.Y], boardPosition.Y, 0));
			boardPosition.X = boardPosition.X + _dropdownTable[boardPosition.X][boardPosition.Y];
		}

		_gameController->Match->CurrentMatchState->Board[boardPosition.X][boardPosition.Y] = tile->GetType();
	});

	for (int i = 0; i < 10; ++i)
	{
		FString row;
		for (int j = 0; j < 10; ++j)
		{
			std::string whitespace = " ";
			row.Append(std::to_string(_gameController->Match->CurrentMatchState->Board[i][j]).c_str()).Append(whitespace.c_str());
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *row);
	}

	bool isCombo = _gameController->Match->CalculateCombo(_destroyTableInfo);
	if (isCombo)
	{
		MarkTilesForDestruction();
		EnlargeComboTiles(_destroyData);
	}
	else if(_gameController->Match->IsYourTurn())
	{
		EventQueue::CallEvent(std::make_shared<EndTurnEvent>(std::bind(&AGrid::OnEndTurn, this, std::placeholders::_1)));
	}
}

void AGrid::OnEndTurn(JSONObjectNode::Ptr response)
{
	UE_LOG(LogTemp, Warning, TEXT("End Turn"));
	_gameController->Match->OnTurnEnded();

	EventQueue::CallEvent(std::make_shared<UpdateCurrentTurnLabelEvent>());
}


