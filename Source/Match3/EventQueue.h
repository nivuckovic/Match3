// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <queue>
#include <string>
#include <map>
#include "GameEvents.h"
#include "GameEventSubscription.h"
#include "ResponseType.h"
#include "ResponseEventSubscription.h"

class MATCH3_API EventQueue
{
public:
	public:
	static void Update();

	static void CallEvent(EventBase::Ptr event);

	template<typename TEvent>
	static EventSubscription::Ptr SubscribeToGameEvent(std::function<void(std::shared_ptr<TEvent>)> callback);
	
	static void UnsubscribeFromAll();
	static void UnsubscribeFromGameEvent(EventSubscription::Ptr& eventSubscription);

	static ResponseEventSubscription::Ptr SubscribeToResponseEvent(ResponseType type, std::function<void(JSONObjectNode::Ptr)> callback);
	static void UnsubscribeFromResponseEvent(ResponseEventSubscription::Ptr& responseEventSubscription);

private:
	EventQueue();

	static void HandleGameEvent(EventBase::Ptr event);
	static void HandleRequestEvent(EventBase::Ptr event);
	static void HandleResponseEvent(EventBase::Ptr event);

private:
	static std::queue<EventBase::Ptr> _queue;
	// Mapa (event tip) - (ptri event subscriptiona)
	static std::map<std::string, std::vector<EventSubscription::Ptr>> _gameEventSubscribers;
	static std::map<std::string, std::function<void(JSONObjectNode::Ptr)>> _directResponseSubscribers;
	static std::map<ResponseType, std::vector<ResponseEventSubscription::Ptr>> _responseEventSubscribers;
	static int _uniqueID;
};

// Pretplati se na event
// Kada se event pozove iz event queuea pozvat ce se odgovaraju callback na objektu
// koji se subscribeao
template <typename TEvent>
EventSubscription::Ptr EventQueue::SubscribeToGameEvent(std::function<void(std::shared_ptr<TEvent>)> callback)
{
	std::string className = typeid(TEvent).name();
	if(!_gameEventSubscribers.count(className))
	{ 
		_gameEventSubscribers[className] = std::vector<EventSubscription::Ptr>();
	}

	EventSubscription::Ptr result = std::make_shared<GameEventSubscription<TEvent>>(_uniqueID++, callback);
	_gameEventSubscribers[className].push_back(result);
	return result;
}
