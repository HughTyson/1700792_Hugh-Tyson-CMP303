#pragma once
#include "SFML/Network.hpp"



enum MESSAGETYPE
{

	m_Client_Lobby,
	m_Server_Lobby,
	m_Connected,
	m_Client_Game,
	m_Server_Game,
	m_Ping
};

struct Message
{
	int type;
	float sent_time;
};

struct Initial_Connect : Message
{
	int PlayerNumber;
};

struct Client_Lobby_Message : Message
{
	bool ready;
	bool exit;
};

struct Server_Lobby_Message : Message
{
	bool start_game;
	int player_number;
};

struct Client_InGame_Message : Message
{
	int player_number;
	float mouse_pos_x;
	float mouse_pos_y;
	float ball_pos_x;
	float ball_pos_y;
	int strokes;
	float angle;
	bool is_hitting;
	bool complete;
	
	float velocity_x;
	float velocity_y;
};

struct Server_InGame_Message : Message
{
	int player_number[2];
	float mouse_pos_x[2];
	float mouse_pos_y[2];
	float ball_pos_x[2];
	float ball_pos_y[2];

	float velocity_x[2];
	float velocity_y[2];
	
	int strokes[2];
	float angle[2];
	bool is_hitting[2];
	bool game_complete;
	

};

class Packets : public sf::Packet
{
public:
	Packets();
	~Packets();
	//functions for sending data
	sf::Packet sendPing(Message m);
	sf::Packet sendInitialData(Initial_Connect i);
	sf::Packet sendClientLobbyData(Client_Lobby_Message cl);
	sf::Packet sendServerLobbyData(Server_Lobby_Message sl);
	sf::Packet sendClientGameData(Client_InGame_Message cg);
	sf::Packet sendServerGameData(Server_InGame_Message sg);

	//functions for recieving data
	Message getType(sf::Packet, Message m);
	Initial_Connect recieveInitialData(sf::Packet temp_pack, Initial_Connect i);
	Client_Lobby_Message recieveClientLobbyData(sf::Packet temp_pack, Client_Lobby_Message cl);
	Server_Lobby_Message recieveServerLobbyData(sf::Packet packet, Server_Lobby_Message sl);

	Client_InGame_Message recieveClientInGameData(sf::Packet temp_packet, Client_InGame_Message cg);
	Server_InGame_Message recieveServerInGameData(sf::Packet temp_packet, Server_InGame_Message cg);


private:

	sf::Packet send_packet;

};

