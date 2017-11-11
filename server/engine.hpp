#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Omnomsock/stdafx.h"
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

class State;

class Engine
{
private:
	WSADATA wsaData;
	int iResult;

	SOCKET ClientSocket = INVALID_SOCKET;
public:
	void loop();
	sf::RenderWindow window;
	std::vector<State*> states;
	State* getState();
	void pushState(State* state);
	void refreshState(int i);
	int state;
	int getInput();
	int init_socket(SOCKET & ClientSocket);
	int check_for_msg(SOCKET ClientSocket);
	int cleanup_socket(SOCKET & ClientSocket);
	Engine();
};