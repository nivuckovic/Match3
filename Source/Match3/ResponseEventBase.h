// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventBase.h"

class MATCH3_API ResponseEventBase : public EventBase
{
public:

	virtual std::string GetEventName() = 0;

	virtual EventType GetEventType() = 0;

	virtual std::string GetRequestGUID() = 0;

public:
	JSONObjectNode::Ptr ResponseData;
};
