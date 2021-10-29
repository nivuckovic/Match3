// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <map>
#include <string>

#include "RequestType.h"

template <typename TEnum>
class MATCH3_API EnumMapBase
{
public:

	std::string EnumToString(TEnum e)
	{
		std::string result = "";

		for (std::pair<const std::string, TEnum>& pair : _lookupTable)
		{
			if (pair.second == e)
			{
				result = pair.first;
				break;
			}
		}

		try
		{
			if (result == "")
				throw std::exception("Enum ne postoji!");
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

		return result;
	}

	TEnum StringToEnum(std::string s)
	{
		try
		{
			return _lookupTable[s];
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

protected:
	std::map<std::string, TEnum> _lookupTable;
};

template <typename TEnum>
class EnumMap : EnumMapBase<TEnum> {};

// Request Type Enum
template<>
class EnumMap<RequestType> : public EnumMapBase<RequestType>
{
public:
	EnumMap()
	{
		_lookupTable = std::map<std::string, RequestType>({
			{ "StartNewGame", RequestType::StartNewGame}
			});
	}
};