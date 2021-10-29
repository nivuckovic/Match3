// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JSONNode.h"

class MATCH3_API JSONIntegerNode : public JSONNode
{
public:
	JSONIntegerNode(int value);

	int GetValue();

	// Inherited via JSONNode
	virtual std::string ToString() override;
private:
	int _value;
};