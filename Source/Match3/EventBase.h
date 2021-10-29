// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <memory>
#include <string>
#include "Request.h"
#include "EventType.h"

class MATCH3_API EventBase
{
public:
	typedef std::shared_ptr<EventBase> Ptr;

	virtual std::string GetEventName() = 0;

	virtual EventType GetEventType() = 0;
};
