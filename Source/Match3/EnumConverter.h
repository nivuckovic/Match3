// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumMap.h"

#include "RequestType.h"
#include <string>
#include <map>

template <typename TEnum>
class MATCH3_API EnumConverter
{
public:
	static std::string EnumToString(TEnum e)
	{
		return _enumMap.EnumToString(e);
	}

	static TEnum StringToEnum(std::string s)
	{
		return _enumMap.StringToEnum(s);
	}

private:
	static EnumMap<TEnum> _enumMap;
};

template <typename TEnum>
EnumMap<TEnum> EnumConverter<TEnum>::_enumMap;