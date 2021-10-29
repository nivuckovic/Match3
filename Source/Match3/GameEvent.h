// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EventBase.h"
#include "RequestEvent.h"
#include "RequestType.h"

/**
 * 
 */
template <typename TEvent>
class MATCH3_API GameEvent : public EventBase
{
public:
	EventType GetEventType() override;
	virtual std::string GetEventName() override;
};

template <typename TEvent>
EventType GameEvent<TEvent>::GetEventType()
{
	return EventType::Game;
}

template<typename TEvent>
inline std::string GameEvent<TEvent>::GetEventName()
{
	return typeid(TEvent).name();
}
