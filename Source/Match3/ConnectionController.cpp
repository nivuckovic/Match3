// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectionController.h"

#include "EventQueue.h"
#include "ResponseType.h"
#include <functional>

void ConnectionController::Begin()
{
	_onNewConnectionSubscription = EventQueue::SubscribeToResponseEvent(ResponseType::NewConnection, std::bind(&ConnectionController::OnNewConnectionResponse, this, std::placeholders::_1));

	Socket::GetInstance().Connect("127.0.0.1", 1234);
}

void ConnectionController::End()
{
	EventQueue::UnsubscribeFromResponseEvent(_onNewConnectionSubscription);

	Socket::GetInstance().Close();
}

void ConnectionController::OnNewConnectionResponse(JSONObjectNode::Ptr response)
{
	_gameController.ConnectionName = response->GetValue<JSONObjectNode::Ptr>("data")->GetValue<std::string>("connectionName");

	_gameController.InGameHUD->OpenHUDWidget<UMainMenuWidget>(FInputModeUIOnly(), true);
}
