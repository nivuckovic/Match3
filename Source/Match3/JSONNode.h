// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include <memory>

class MATCH3_API JSONObjectNode;

class JSONNode
{
public:
	typedef std::shared_ptr<JSONNode> Ptr;

	virtual std::string ToString() = 0;
};

