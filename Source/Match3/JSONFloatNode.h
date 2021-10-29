// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JSONNode.h"

class MATCH3_API JSONFloatNode : public JSONNode
{
public:
	JSONFloatNode(float value);

	float GetValue();

	// Inherited via JSONNode
	virtual std::string ToString() override;

private:
	float _value;
};
