// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchGameWidget.h"

#include "MatchController.h"
#include "EventQueue.h"

void UMatchGameWidget::OnOpen()
{
	UpdateCurrentTurnLabel();

	_updateCurrentTurnLabelSubscription = EventQueue::SubscribeToGameEvent<UpdateCurrentTurnLabelEvent>(std::bind(&UMatchGameWidget::OnUpdateCurrentTurnLabelEvent, this, std::placeholders::_1));
}

void UMatchGameWidget::OnClose()
{
	if (_updateCurrentTurnLabelSubscription != nullptr)
		EventQueue::UnsubscribeFromGameEvent(_updateCurrentTurnLabelSubscription);
}

void UMatchGameWidget::OnUpdateCurrentTurnLabelEvent(std::shared_ptr<UpdateCurrentTurnLabelEvent> data)
{
	UpdateCurrentTurnLabel();
}

void UMatchGameWidget::UpdateCurrentTurnLabel()
{
	std::string playerOpponentText = (_gameController->Match->PlayerId == _gameController->Match->CurrentMatchState->CurrentTurn) ? "Player" : "Opponent";
	FString currentTurnText(("Current turn: " + playerOpponentText).c_str());
	CurrentTurnLabel->SetText(FText::FromString(currentTurnText));
}
