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

	//game info

	sf::Vector2f ball_pos;
	sf::Vector2f mouse_pos;
	int strokes;
	bool level_complete;
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

	int players_connected;
	int max_players;
	serverState _state;
	bool start_game;
	bool close_server;

	sf::TcpSocket tcpClient[2];
	
	sf::TcpListener listener;

	ClientInfo *clientInfo[2];

	//packets

	Packets packets;
	Message incoming;
	Initial_Connect i_connect;
	Client_Lobby_Message cl_message;
	Server_Lobby_Message sl_message;
	
	Client_InGame_Message cg_message;
	Server_InGame_Message sg_message;

	//timing varibles

	sf::Clock networkUpdateTimer;
	sf::Clock gameTime;
	float clientUpdateTime;

	//varibles for game state

	bool finish_game;
	bool just_joined[2];

	float m_Time;
	bool player1_shot = true;

};

