// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDecodable.h"

#include <array>
#include "Enums.h"

class MATCH3_API MatchState : public IDecodable
{
public:
	void Decode(JSONObjectNode::Ptr node) override;

public:
	std::array<std::array<int, 10>, 10> Board;
	MatchTurn CurrentTurn;
};
