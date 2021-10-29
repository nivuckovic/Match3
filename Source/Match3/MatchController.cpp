// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchController.h"

#include <functional>
#include "EventQueue.h"
#include "MatchLevel.h"
#include "GameController.h"
#include "InGameHUD.h"
#include "Enums.h"

void MatchController::Begin()
{
	// _onNewGameStartedSubscription = EventQueue::SubscribeToResponseEvent(ResponseType::StartedNewGame, std::bind(&MatchController::OnNewGameStarted, this, std::placeholders::_1));
}

void MatchController::End()
{
	// EventQueue::UnsubscribeFromResponseEvent(_onNewGameStartedSubscription);
}

void MatchController::OnNewGameStarted(JSONObjectNode::Ptr response)
{
	JSONObjectNode::Ptr data = response->GetValue<JSONObjectNode::Ptr>("data");

	CurrentMatchState = std::make_shared<MatchState>();
	CurrentMatchState->Decode(data);

	_gameController.Match->PlayerId = static_cast<MatchTurn>(data->GetValue<int>("startingTurn"));

	// ovo izbaci iz controlera
	FVector position(0, 0, 0);
	FRotator rotation(0, 0, 0);

	FTransform transform;
	transform.SetTranslation(position);
	transform.SetRotation(FQuat(rotation));

	AMatchLevel* matchLevel = _gameController.GetWorld()->SpawnActorDeferred<AMatchLevel>(_gameController.MatchLevelClass, transform);
	matchLevel->SetGameController(&_gameController);
	matchLevel->FinishSpawning(transform);
}

bool MatchController::WillItBeComboAfterSwap(FVector firstBoardPosition, FVector secondBoardPosition, std::array<std::array<bool, 10>, 10>& tilesDestroyTable)
{
	std::swap(CurrentMatchState->Board[firstBoardPosition.X][firstBoardPosition.Y], CurrentMatchState->Board[secondBoardPosition.X][secondBoardPosition.Y]);

	bool isCombo = CalculateCombo(tilesDestroyTable);

	std::swap(CurrentMatchState->Board[firstBoardPosition.X][firstBoardPosition.Y], CurrentMatchState->Board[secondBoardPosition.X][secondBoardPosition.Y]);

	return isCombo;
}

bool MatchController::CalculateCombo(std::array<std::array<bool, 10>, 10>& tilesDestroyTable)
{
	tilesDestroyTable = std::array<std::array<bool, 10>, 10>({});


	bool isCombo = false;
	std::array<std::array<int, 10>, 10> _horizontalComboBoard;
	std::array<std::array<int, 10>, 10> _verticalComboBoard;

	// Horizontal combo
	for (int row = 0; row < 10; ++row)
	{
		for (int column = 0; column < 10; ++column)
		{
			if (column == 0)
			{
				_horizontalComboBoard[row][column] = 1;
				continue;
			}

			if (CurrentMatchState->Board[row][column - 1] == CurrentMatchState->Board[row][column])
			{
				_horizontalComboBoard[row][column] = _horizontalComboBoard[row][column - 1] + 1;
			}
			else
			{
				_horizontalComboBoard[row][column] = 1;
			}
		}
	}

	// Horizontal
	for (int row = 0; row < 10; ++row)
	{
		int column = 9;

		while (column >= 0)
		{
			if (_horizontalComboBoard[row][column] >= 3)
			{
				for (int i = 0; i < _horizontalComboBoard[row][column]; ++i)
				{
					tilesDestroyTable[row][column - i] = true;
				}

				isCombo = true;
			}

			column -= _horizontalComboBoard[row][column];
		}
	}

	// Vertical combo
	for (int row = 0; row < 10; ++row)
	{
		for (int column = 0; column < 10; ++column)
		{
			if (row == 0) {
				_verticalComboBoard[row][column] = 1;
				continue;
			}

			if (CurrentMatchState->Board[row][column] == CurrentMatchState->Board[row - 1][column])
			{
				_verticalComboBoard[row][column] = _verticalComboBoard[row - 1][column] + 1;
			}
			else
			{
				_verticalComboBoard[row][column] = 1;
			}
		}
	}

	// Vertical 
	for (int column = 0; column < 10; ++column)
	{
		int row = 9;

		while (row >= 0)
		{
			if (_verticalComboBoard[row][column] >= 3)
			{
				for (int i = 0; i < _verticalComboBoard[row][column]; ++i)
				{
					tilesDestroyTable[row - i][column] = true;
				}

				isCombo = true;
			}

			row -= _verticalComboBoard[row][column];
		}
	}
	
	return isCombo;
}

std::array<int, 10> MatchController::CalculateDropdownCount(std::array<std::array<bool, 10>, 10> tilesDestroyTable)
{
	std::array<int, 10> result {}; // Initializes all elements to zero

	for (int column = 0; column < 10; ++column)
	{
		for (int row = 0; row < 10; ++row)
		{
			if (tilesDestroyTable[row][column])
				++result[column];
		}
	}

	return result;
}

std::array<std::array<int, 10>, 10> MatchController::CalculateDropdownTable(std::array<std::array<bool, 10>, 10> tilesDestroyTable)
{
	std::array<std::array<int, 10>, 10> result{};

	for (int column = 0; column < 10; ++column)
	{
		int dropdownCount = 0;
		for (int row = 9; row >= 0; --row)
		{
			if (tilesDestroyTable[row][column])
			{
				dropdownCount += 1;
				continue;
			}

			result[row][column] = dropdownCount;
		}
	}

	return result;
}

void MatchController::OnTurnEnded()
{
	// int currentTurnInt = static_cast<int>(_gameController.Match->CurrentMatchState->CurrentTurn);
	// _gameController.Match->CurrentMatchState->CurrentTurn = static_cast<MatchTurn>((currentTurnInt + 1) % 2);

	if (_gameController.Match->CurrentMatchState->CurrentTurn == MatchTurn::Player)
		_gameController.Match->CurrentMatchState->CurrentTurn = MatchTurn::Opponent;
	else
		_gameController.Match->CurrentMatchState->CurrentTurn = MatchTurn::Player;
}

bool MatchController::IsYourTurn()
{
	return _gameController.Match->PlayerId == _gameController.Match->CurrentMatchState->CurrentTurn;
}
