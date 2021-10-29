// Fill out your copyright notice in the Description page of Project Settings.


#include "ResponseEvent.h"
#include <string>
#include "JSONParser.h"

ResponseEvent::ResponseEvent(std::string content)
{
	ResponseData = JSONParser::GetInstance().Decode(content);
}

std::string ResponseEvent::GetEventName()
{
	throw std::logic_error("The method or operation is not implemented.");
}

EventType ResponseEvent::GetEventType()
{
	return EventType::Response;
}

std::string ResponseEvent::GetRequestGUID()
{
	return ResponseData->GetValue<std::string>("responseTo");
}

ResponseType ResponseEvent::GetResponseType()
{
	return static_cast<ResponseType>(ResponseData->GetValue<int>("responseType"));
}

