// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JSONNode.h"

class MATCH3_API JSONBoolNode : public JSONNode
{
public:
	JSONBoolNode(bool value);

	virtual std::string ToString() override;

	bool GetValue();

private:
	bool _value;
};