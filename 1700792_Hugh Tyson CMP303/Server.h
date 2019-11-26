#pragma once
#include <iostream>
#include "SFML/Network.hpp"
#include "Packets.h"

enum serverState
{
	INIT_CONNECT, SERVER_LOBBY, SERVER_GAME
};

struct ClientInfo
{
public:

	bool connected;
	std::string player_name;
	int player_number;

	sf::IpAddress ip;
	int port;
	
	bool host;

	//Lobby Info

	bool player_ready;
	bool player_exit;

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

	void updateServer();

	void dissconenctAll();
	void wipeClient(int i);

	//varibles for the server
	sf::IpAddress ip;
	int port;
	int port_udp;
	int players_connected;
	int max_players;
	serverState _state;
	bool start_game;
	bool close_server;

	sf::TcpSocket tcpClient[2];
	sf::UdpSocket udpClient[2];
	
	sf::TcpListener listener;

	ClientInfo *clientInfo[2];

	//packets

	Packets packets;
	Message incoming;
	Initial_Connect i_connect;
	Client_Lobby_Message cl_message;
	Server_Lobby_Message sl_message;

};

