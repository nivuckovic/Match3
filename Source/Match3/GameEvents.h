// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameEvent.h"
#include "RequestEvent.h"
#include "RequestType.h"

#include <vector>

class UpdateCurrentTurnLabelEvent : public GameEvent<UpdateCurrentTurnLabelEvent>
{
public:
	UpdateCurrentTurnLabelEvent() {};
};

class StartNewGameEvent : public RequestEvent
{
public:

	StartNewGameEvent()
	{
	}

	Request GenerateRequest() override
	{
		Request request = Request::GenerateRequest(RequestType::StartNewGame);

		return request;
	}
};

class CancelStartNewGameEvent : public RequestEvent
{
public:

	CancelStartNewGameEvent() {}

	Request GenerateRequest() override
	{
		Request request = Request::GenerateRequest(RequestType::CancelStartNewGame);
		return request;
	}

};

class TileMoveEvent : public RequestEvent
{
public:
	int _firstX;
	int _firstY;
	int _secondX;
	int _secondY;

	std::function<void(JSONObjectNode::Ptr)> _callback;

	TileMoveEvent(int firstX, int firstY, int secondX, int secondY, std::function<void(JSONObjectNode::Ptr)> callback)
	{
		_firstX = firstX;
		_firstY = firstY;
		_secondX = secondX;
		_secondY = secondY;

		_callback = callback;
	}

	Request GenerateRequest() override
	{
		Request request = Request::GenerateRequest(RequestType::TileMove);

		request.Data->AddValue<int>("firstX", _firstX);
		request.Data->AddValue<int>("firstY", _firstY);
		request.Data->AddValue<int>("secondX", _secondX);
		request.Data->AddValue<int>("secondY", _secondY);

		request.Callback = _callback;

		return request;
	}
};

class GenerateNewTilesEvent : public RequestEvent
{
public:

	std::vector<int> _dropdownInfo;
	std::function<void(JSONObjectNode::Ptr)> _callback;

	GenerateNewTilesEvent(std::vector<int> dropdownInfo, std::function<void(JSONObjectNode::Ptr)> callback) : _dropdownInfo(dropdownInfo), _callback(callback) {}

	Request GenerateRequest() override
	{
		Request request = Request::GenerateRequest(RequestType::GenerateNewTiles);

		request.Data->AddValue<std::vector<int>>("dropdownInfo", _dropdownInfo);
		request.Callback = _callback;

		return request;
	}

};

class EndTurnEvent : public RequestEvent
{
public:
	std::function<void(JSONObjectNode::Ptr)> _callback;

	EndTurnEvent(std::function<void(JSONObjectNode::Ptr)> callback) : _callback(callback) {}

	Request GenerateRequest() override
	{
		Request request = Request::GenerateRequest(RequestType::EndTurn);
		
		request.Callback = _callback;

		return request;
	}

};