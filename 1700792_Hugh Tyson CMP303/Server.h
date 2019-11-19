#pragma once
#include <iostream>
#include "SFML/Network.hpp"
#include "Packets.h"

enum serverState
{
	SERVER_LOBBY, SERVER_GAME
};

struct ClientInfo
{
public:
	sf::IpAddress ip;
	int port;
	int player_number;
	bool host;
};

class Server
{

private:

public:
	Server();
	~Server();

	void update();

private:

	//functions to run the server

	void AddPlayer();
	void RecieveMessage();
	void SendMessage();

	

	//varibles for the server
	sf::IpAddress ip;
	int port;
	int players_connected;
	int max_players;
	serverState _state;

	sf::TcpSocket tcpClient[2];
	sf::TcpListener listener;

	std::vector<ClientInfo> clientInfo;
	ClientInfo temp_info;

	//packets

	Packets packets;
	Initial_Connect i_connect;
	Client_Lobby_Message l_message;
};

