#include "stdafx.h"
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 64
#define DEFAULT_PORT "2222"

int init_socket(SOCKET& ClientSocket) {
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	//SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cout << "WSAStartup failed with error: " << iResult << std::endl;
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		std::cout << "getaddrinfo failed with error: " << iResult << std::endl;
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		std::cout << "bind failed with error: " << WSAGetLastError() << std::endl;
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		std::cout << "listen failed with error: " << WSAGetLastError() << std::endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		std::cout << "accept failed with error: " << WSAGetLastError() << std::endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// No longer need server socket
	closesocket(ListenSocket);

	int iTimeout = 1;
	setsockopt(ClientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&iTimeout, sizeof(iTimeout));
}

int check_for_msg(SOCKET ClientSocket) {
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult, iSendResult;

	iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
	if (iResult > 0) {
		std::cout << "Bytes received: " << iResult << std::endl;
		if (strncmp(recvbuf, "left\n", 5) == 0) {
			std::cout << "left" << std::endl;
			return 1;
		}
		if (strncmp(recvbuf, "right\n", 6) == 0) {
			std::cout << "right" << std::endl;
			return 2;
		}
		if (strncmp(recvbuf, "up\n", 3) == 0) {
			std::cout << "up" << std::endl;
			return 3;
		}
		if (strncmp(recvbuf, "down\n", 5) == 0) {
			std::cout << "down" << std::endl;
			return 4;
		}
		return 0;
	}
	else if (iResult == 0)
		std::cout << "Connection closing..." << std::endl;
	else {
		int iError = WSAGetLastError();
		if (iError == WSAETIMEDOUT) {
			iResult = 1;
			return 0;
		}
		std::cout << "recv failed with error: " << iError << std::endl;

		closesocket(ClientSocket);
		WSACleanup();
		return -1;
	}
}

int cleanup_socket(SOCKET& ClientSocket) {
	// shutdown the connection since we're done
	int iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		std::cout << "shutdown failed with error: " << WSAGetLastError() << std::endl;
		closesocket(ClientSocket);
		WSACleanup();
		return -1;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();
}

int __cdecl main(void)
{
	SOCKET ClientSocket = INVALID_SOCKET;
	// Note, this will block until we get a connection.
	init_socket(ClientSocket);

	int iResult = 0;

	do {
		// Net latency 1ms.
		iResult = check_for_msg(ClientSocket);
		// -1 : error
		//  0 : timeout/garbage
		//  1 : left
		//  2 : right
		//  3 : up
		//  4 : down
	} while (iResult >= 0);

	cleanup_socket(ClientSocket);
	return 0;
}
