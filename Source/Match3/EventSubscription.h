// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventBase.h"
#include <functional>

/**
 * 
 */
class MATCH3_API EventSubscription
{
public:
	typedef std::shared_ptr<EventSubscription> Ptr;

	virtual void Callback(EventBase::Ptr event) = 0;

	virtual std::string GetEventType() = 0;

	const int ID;

protected:
	EventSubscription(int id) : ID(id) {};
};
