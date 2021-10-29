// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchState.h"

void MatchState::Decode(JSONObjectNode::Ptr node)
{
	std::vector<int> board = node->GetValue<JSONObjectNode::Ptr>("match")->GetValue<std::vector<int>>("board");

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			Board[i][j] = board[i * 10 + j];
		}
	}

	CurrentTurn = static_cast<MatchTurn>(node->GetValue<JSONObjectNode::Ptr>("match")->GetValue<int>("turn"));
}
