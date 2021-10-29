// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseController.h"
#include "MatchState.h"
#include "JSONObjectNode.h"
#include "ResponseEventSubscription.h"
#include <array>
#include "Enums.h"


class GameController;

class MATCH3_API MatchController : public BaseController
{
public:
	MatchController(UGameController& gameController) : BaseController(gameController) {};

	void Begin() override;
	void End() override;

	void OnNewGameStarted(JSONObjectNode::Ptr response);

	bool WillItBeComboAfterSwap(FVector firstBoardPosition, FVector secondBoardPosition, std::array<std::array<bool, 10>, 10>& outTilesDestroyTable);
	bool CalculateCombo(std::array<std::array<bool, 10>, 10>& outTilesDestroyTable);
	std::array<int, 10> CalculateDropdownCount(std::array<std::array<bool, 10>, 10> tilesDestroyTable);

	std::array<std::array<int, 10>, 10> CalculateDropdownTable(std::array<std::array<bool, 10>, 10> tilesDestroyTable);

	void OnTurnEnded();
	bool IsYourTurn();

public:
	std::shared_ptr<MatchState> CurrentMatchState;
	MatchTurn PlayerId;

private:
};
