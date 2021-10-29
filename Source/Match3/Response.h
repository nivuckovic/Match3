// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Message.h"
#include "IEncodable.h"
#include "IDecodable.h"
#include "RequestType.h"
#include <map>
#include "JSONObjectNode.h"


class MATCH3_API Response : public Message, public IDecodable
{
public:
	Response() {};

	// Inherited via IDecodable
	virtual void Decode(JSONObjectNode::Ptr node) override;

public:
	JSONObjectNode::Ptr Data;
	RequestType Type;
};