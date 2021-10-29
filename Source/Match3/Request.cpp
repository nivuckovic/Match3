// Fill out your copyright notice in the Description page of Project Settings.


#include "Request.h"
#include <ctime>
#include "Misc/Guid.h"
#include "Misc/DateTime.h"
#include "EnumConverter.h"
#include "RequestType.h"

Request::Request()
{
	Callback = [](JSONObjectNode::Ptr) {};
}

Request Request::GenerateRequest(RequestType requestType)
{
	Request request;

	request.Identifier = TCHAR_TO_UTF8(*(FGuid::NewGuid().ToString()));
	request.Timestamp = FDateTime::Now().GetSecond();
	request.Type = requestType;

	request.Data = std::make_shared<JSONObjectNode>();

	return request;
}

JSONObjectNode::Ptr Request::Encode()
{
	JSONObjectNode::Ptr requestNode = std::make_shared<JSONObjectNode>();

	requestNode->AddValue<std::string>("identifier", Identifier);
	requestNode->AddValue<int>("timestamp", Timestamp);
	requestNode->AddValue<int>("requestType", static_cast<int>(this->Type));
	
	requestNode->AddValue<JSONObjectNode::Ptr>("data", Data);
	
	return requestNode;
}