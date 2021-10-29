// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventBase.h"

class Request;

class MATCH3_API RequestEvent : public EventBase
{
public:
	virtual Request GenerateRequest() = 0;
	
	EventType GetEventType() override;

public:
	std::function<void(JSONObjectNode::Ptr)> Callback;

private:
	virtual std::string GetEventName() override;
};

