// Fill out your copyright notice in the Description page of Project Settings.


#include "EventQueue.h"
#include "RequestEvent.h"
#include "Request.h"
#include "Socket.h"
#include "EventType.h"
#include "ResponseEvent.h"
#include "GameEventSubscription.h"

std::queue<EventBase::Ptr> EventQueue::_queue;
std::map<std::string, std::vector<EventSubscription::Ptr>> EventQueue::_gameEventSubscribers;
std::map<std::string, std::function<void(JSONObjectNode::Ptr)>> EventQueue::_directResponseSubscribers;
std::map<ResponseType, std::vector<ResponseEventSubscription::Ptr>> EventQueue::_responseEventSubscribers;
int EventQueue::_uniqueID = 0;

void EventQueue::CallEvent(EventBase::Ptr event)
{
	_queue.push(std::static_pointer_cast<EventBase>(event));
}

void EventQueue::Update()
{
	while (!_queue.empty())
	{
		EventBase::Ptr nextEvent = _queue.front();
		_queue.pop();

		switch (nextEvent->GetEventType())
		{
		case EventType::Game:
			HandleGameEvent(nextEvent);
			break;
		case EventType::Request:
			HandleRequestEvent(nextEvent);
			break;
		case EventType::Response:
			HandleResponseEvent(nextEvent);
			break;
		}
	}
}

void EventQueue::UnsubscribeFromAll()
{
	_gameEventSubscribers.clear();
	_directResponseSubscribers.clear();
	_responseEventSubscribers.clear();
}

void EventQueue::UnsubscribeFromGameEvent(EventSubscription::Ptr& eventSubscription)
{
	int subscriptionID = eventSubscription->ID;
	std::string key = eventSubscription->GetEventType();
	
	if (_gameEventSubscribers.count(key))
	{
		// Remove subscription from vector
		_gameEventSubscribers[key].erase(
			std::remove_if(_gameEventSubscribers[key].begin(), _gameEventSubscribers[key].end(), [&subscriptionID](EventSubscription::Ptr x) {
			return subscriptionID == x->ID;
		}));
	}

	eventSubscription.reset();
}

void EventQueue::UnsubscribeFromResponseEvent(ResponseEventSubscription::Ptr& responseEventSubscription)
{
	int subscriptionID = responseEventSubscription->Id;
	ResponseType type = responseEventSubscription->Type;

	if (_responseEventSubscribers.count(type))
	{
		// Remove subscription from vector
		_responseEventSubscribers[type].erase(
			std::remove_if(_responseEventSubscribers[type].begin(), _responseEventSubscribers[type].end(), [&subscriptionID](ResponseEventSubscription::Ptr x) {
			return subscriptionID == x->Id;
		}), _responseEventSubscribers[type].end());
	}

	responseEventSubscription.reset();
}

ResponseEventSubscription::Ptr EventQueue::SubscribeToResponseEvent(ResponseType type, std::function<void(JSONObjectNode::Ptr)> callback)
{
	ResponseEventSubscription::Ptr subscription = std::make_shared<ResponseEventSubscription>(type, _uniqueID++, callback);

	if (!_responseEventSubscribers.count(type))
	{
		_responseEventSubscribers[type] = std::vector<ResponseEventSubscription::Ptr>();
	}
	_responseEventSubscribers[type].push_back(subscription);
	
	return subscription;
}

void EventQueue::HandleGameEvent(EventBase::Ptr event)
{
	std::string className = event->GetEventName();
	if (_gameEventSubscribers.count(className))
	{
		// Notify subscribers
		std::for_each(_gameEventSubscribers[className].begin(), _gameEventSubscribers[className].end(), [&event](EventSubscription::Ptr& eventSubscription) {
			eventSubscription->Callback(event);
		});
	}
}

void EventQueue::HandleRequestEvent(EventBase::Ptr event)
{
	std::shared_ptr<RequestEvent> requestEvent = std::static_pointer_cast<RequestEvent>(event);
	Request request = requestEvent->GenerateRequest();

	_directResponseSubscribers[request.Identifier] = request.Callback;

	Socket::GetInstance().SendMessage(request);
}

void EventQueue::HandleResponseEvent(EventBase::Ptr event)
{
	std::shared_ptr<ResponseEvent> responseEvent = std::static_pointer_cast<ResponseEvent>(event);

	if (_directResponseSubscribers.count(responseEvent->GetRequestGUID()))
	{
		auto it = _directResponseSubscribers.find(responseEvent->GetRequestGUID());
		it->second(responseEvent->ResponseData);
		_directResponseSubscribers.erase(it);
	}
		
	if (_responseEventSubscribers.count(responseEvent->GetResponseType()))
		std::for_each(_responseEventSubscribers[responseEvent->GetResponseType()].begin(), _responseEventSubscribers[responseEvent->GetResponseType()].end(), [&responseEvent](ResponseEventSubscription::Ptr subscription){
		subscription->Callback(responseEvent->ResponseData);
	});
}
