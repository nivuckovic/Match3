// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResponseType.h"

class MATCH3_API ResponseEventSubscription 
{
public:
	ResponseEventSubscription(ResponseType type, int id, std::function<void(JSONObjectNode::Ptr)> callback) : Id(id), Callback(callback), Type(type) {};

	typedef std::shared_ptr<ResponseEventSubscription> Ptr;


public:
	std::function<void(JSONObjectNode::Ptr)> Callback;
	int Id;
	ResponseType Type;
};
