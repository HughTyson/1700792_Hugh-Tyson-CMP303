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
	
	bool getServerRunning() { return server_running; }	
	

	
protected:

	//functions for client to server
	void connect_player();

	int players_connected;
	sf::Thread network_thread;
	sf::IpAddress ip;
	bool server_running = false;
	int port = 53000;
	sf::TcpSocket connector;
	//packet variables
	
	Packets packet;
	Initial_Connect i_connect;
	Client_Lobby_Message l_message;
};
