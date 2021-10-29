// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventBase.h"

class MATCH3_API RequestEventBase : public EventBase
{
public:
	virtual Request GenerateRequest() = 0;

	virtual std::string GetEventName() = 0;

	virtual EventType GetEventType() = 0;

};
