// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseController.h"
#include "ResponseEventSubscription.h"
#include "JSONObjectNode.h"
#include "Socket.h"

class UGameController;

class MATCH3_API ConnectionController : public BaseController
{

public:
	ConnectionController(UGameController& gameController) : BaseController(gameController) {};

	void Begin() override;
	void End() override;

	void OnNewConnectionResponse(JSONObjectNode::Ptr response);

private:
	ResponseEventSubscription::Ptr _onNewConnectionSubscription;
};
