// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EventSubscription.h"
#include <functional>

template<typename TEvent>
class MATCH3_API GameEventSubscription : public EventSubscription
{
public:
	typedef std::shared_ptr<GameEventSubscription> Ptr;
	GameEventSubscription(int id, std::function<void(std::shared_ptr<TEvent>)> callback) : EventSubscription(id), _callback(callback) {};

	// Inherited via EventSubscription
	virtual void Callback(EventBase::Ptr event) override;
	// Inherited via EventSubscription
	virtual std::string GetEventType() override;

private:
	std::function<void(std::shared_ptr<TEvent>)> _callback;
};

template<typename TEvent>
inline void GameEventSubscription<TEvent>::Callback(EventBase::Ptr event)
{
	_callback(std::static_pointer_cast<TEvent>(event));
}

template<typename TEvent>
inline std::string GameEventSubscription<TEvent>::GetEventType()
{
	return typeid(TEvent).name();
}