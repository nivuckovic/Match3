// Fill out your copyright notice in the Description page of Project Settings.


#include "RequestEvent.h"

EventType RequestEvent::RequestEvent::GetEventType()
{
	return EventType::Request;
}

std::string RequestEvent::RequestEvent::GetEventName()
{
	return "RequestEvent";
}
