#pragma once
#include "Server.h"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "Server_Init.h"
#include "Packets.h"

class NetworkingManager
{
public:
	NetworkingManager();
	~NetworkingManager();

	void server_init();

	void lobby_update(bool ready, bool exit);
	bool lobby_recive(bool start_game);
	
	bool getServerRunning() { return server_running; }	
	
	//functions for client to server
	bool connect_player();
	
protected:



	int players_connected;
	sf::Thread network_thread;
	sf::IpAddress ip;
	bool server_running = false;
	int port = 53000;
	sf::TcpSocket connector;
	//packet variables
	
	Message incoming;
	Initial_Connect i_connect;
	Client_Lobby_Message l_message;
	Server_Lobby_Message sl_message;
	
};

