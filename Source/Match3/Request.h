// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Message.h"
#include "IEncodable.h"
#include "IDecodable.h"
#include "RequestType.h"
#include <map>
#include "JSONNode.h"
#include <functional>
#include "Response.h"


class MATCH3_API Request : public Message, public IEncodable
{
public:
	static Request GenerateRequest(RequestType requestType);

	// Inherited via IDecodable
	virtual JSONObjectNode::Ptr Encode() override;

private:
	Request();

public:
	JSONObjectNode::Ptr Data;
	RequestType Type;
	std::function<void(JSONObjectNode::Ptr)> Callback;
};

