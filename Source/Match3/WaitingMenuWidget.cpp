// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingMenuWidget.h"

#include "GameController.h"
#include "InGameHUD.h"
#include "MainMenuWidget.h"
#include <functional>
#include "ResponseType.h"
#include "EventQueue.h"
#include "GameEvents.h"
#include "RequestType.h"
#include "MatchController.h"
#include "MatchGameWidget.h"

UWaitingMenuWidget::UWaitingMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) 
{
	
}

void UWaitingMenuWidget::OnReturnToMainMenuClicked()
{
	_gameController->InGameHUD->OpenHUDWidget<UMainMenuWidget>(FInputModeUIOnly(), true);
}

void UWaitingMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UWaitingMenuWidget::Initialize()
{
	Super::Initialize();

	return true;
}

void UWaitingMenuWidget::OnOpen()
{
	EventQueue::CallEvent(std::make_shared<StartNewGameEvent>());
	_matchFoundSubscription = EventQueue::SubscribeToResponseEvent(ResponseType::StartedNewGame, std::bind(&UWaitingMenuWidget::OnMatchFound, this, std::placeholders::_1));

	FString connectionName(("Connection: " + _gameController->ConnectionName).c_str());
	ConnectionNameLabel->SetText(FText::FromString(connectionName));
}

void UWaitingMenuWidget::OnClose()
{
	EventQueue::CallEvent(std::make_shared<CancelStartNewGameEvent>());
	EventQueue::UnsubscribeFromResponseEvent(_matchFoundSubscription);
}

void UWaitingMenuWidget::OnMatchFound(JSONObjectNode::Ptr response)
{
	_gameController->Match->OnNewGameStarted(response);
	_gameController->InGameHUD->OpenHUDWidget<UMatchGameWidget>(FInputModeGameAndUI(), true);
}
