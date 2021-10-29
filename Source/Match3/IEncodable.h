// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JSONObjectNode.h"

class MATCH3_API IEncodable
{
public:
	virtual JSONObjectNode::Ptr Encode() = 0;
};
