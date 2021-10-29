// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JSONObjectNode.h"

class MATCH3_API IDecodable
{
public:
	virtual void Decode(JSONObjectNode::Ptr node) = 0;
};