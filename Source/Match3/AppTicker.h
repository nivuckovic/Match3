// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <vector>
#include <functional>

class MATCH3_API AppTicker
{
public:

	static void Subscribe();

private:
	static std::vector<std::function<void()>> _subscribers;
};
