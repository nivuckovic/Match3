// Fill out your copyright notice in the Description page of Project Settings.


#include "JSONFloatNode.h"

JSONFloatNode::JSONFloatNode(float value) : _value(value)
{
}

float JSONFloatNode::GetValue()
{
	return _value;
}

std::string JSONFloatNode::ToString()
{
	return std::to_string(_value);
}
