// Fill out your copyright notice in the Description page of Project Settings.


#include "Socket.h"
#include "JSONParser.h"
#include "EventQueue.h"
#include "ResponseEvent.h"

char Socket::DELIMITER = static_cast<char>(158);

bool Socket::Connect(FString ipAddress, int port)
{
    bool success = true;

	FIPv4Address ipv4Address;
	FIPv4Address::Parse(FString("127.0.0.1"), ipv4Address);
	FIPv4Endpoint endpoint(ipv4Address, (uint16)1234);

	_socket = std::unique_ptr<FSocket>(FTcpSocketBuilder(TEXT("TcpSocket")).AsNonBlocking().AsReusable());

	ISocketSubsystem* socketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

	TSharedRef<FInternetAddr> internetAddress = socketSubsystem->CreateInternetAddr();
	internetAddress->SetIp(endpoint.Address.Value);
	internetAddress->SetPort(endpoint.Port);

	_socket->Connect(*internetAddress);

    return success;
}

void Socket::Close()
{
	if(_socket != nullptr)
		_socket->Close();
}

void Socket::SendMessage(std::string message)
{
	message += DELIMITER;

	FString logMsg(message.c_str());
	UE_LOG(LogTemp, Warning, TEXT("SALJEM: %s"), *logMsg);

	const uint8* byteMessage = reinterpret_cast<const uint8_t*>(message.c_str());

	int bytesSent = 0;
	_socket->Send(byteMessage, message.size() * sizeof(uint8_t), bytesSent);
}

void Socket::SendMessage(Request& request)
{
	SendMessage(request.Encode()->ToString());
}

void Socket::CheckForPendingData()
{
	uint32 pendingDataSize;
	if (_socket->HasPendingData(pendingDataSize))
		ReceiveMessage(pendingDataSize);

}

void Socket::ReceiveMessage(uint32 pendingDataSize)
{
	uint8* byteMessage = new uint8[pendingDataSize];
	int bytesRead;
	_socket->Recv(byteMessage, pendingDataSize, bytesRead);

	std::string receivedMessage = std::string(byteMessage, byteMessage + bytesRead);
	std::vector<std::string> messages = SplitString(receivedMessage, DELIMITER);

	for (std::string message : messages)
	{
		EventQueue::CallEvent(std::make_shared<ResponseEvent>(receivedMessage));
	}
}

std::vector<std::string> Socket::SplitString(std::string message, char delimiter)
{
	std::vector<std::string> result;

	size_t pos = 0;
	std::string token;
	while ((pos = message.find(delimiter)) != std::string::npos) {
		result.push_back(token = message.substr(0, pos));

		message.erase(0, pos + 1); // 1 = delimiter length
	}

	if (message.size() > 0)
		result.push_back(message);

	return result;
}
