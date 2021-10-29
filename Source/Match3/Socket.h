// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Sockets.h"
#include <memory>
#include <Runtime/Networking/Public/Interfaces/IPv4/IPv4Address.h>
#include <Runtime/Networking/Public/Interfaces/IPv4/IPv4Endpoint.h>
#include "Common/TcpSocketBuilder.h"
#include <string>
#include "Request.h"
#include <vector>

class MATCH3_API Socket
{
public:
	static Socket& GetInstance()
	{
		static Socket instance;

		return instance;
	}

	bool Connect(FString ipAddress, int port);
	void Close();

	void SendMessage(Request& request);
	void SendMessage(std::string message);

	void CheckForPendingData();

private:
	Socket() { UE_LOG(LogTemp, Warning, TEXT("Napravljen novi socket!")); };

	void ReceiveMessage(uint32 pendingDataSize);

private:
	std::unique_ptr<FSocket> _socket;

	std::vector<std::string> SplitString(std::string message, char delimiter);

	static char DELIMITER;
};
