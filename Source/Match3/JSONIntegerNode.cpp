// Fill out your copyright notice in the Description page of Project Settings.


#include "JSONIntegerNode.h"

JSONIntegerNode::JSONIntegerNode(int value) : _value(value)
{
}

int JSONIntegerNode::GetValue()
{
	return _value;
}

std::string JSONIntegerNode::ToString()
{
	return std::to_string(_value);
}
