// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResponseEventBase.h"
#include "Response.h"
#include "JSONObjectNode.h"
#include "ResponseType.h"

class MATCH3_API ResponseEvent : public EventBase
{
public:
	ResponseEvent(std::string content);

	std::string GetEventName() override;
	EventType GetEventType() override;
	
	virtual std::string GetRequestGUID();
	ResponseType GetResponseType();

public:
	JSONObjectNode::Ptr ResponseData;

private:
	std::function<void(JSONObjectNode::Ptr)> Callback;
};
