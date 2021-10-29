// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "JSONNode.h"

class MATCH3_API JSONStringNode : public JSONNode
{
public:
	JSONStringNode(std::string value);

	std::string GetValue();

	virtual std::string ToString() override;

private:
	std::string _value;
};
