#pragma once
#include "SFML/Network.hpp"

struct Initial_Connect
{
	std::string PlayerName;
};

enum MESSAGETYPE
{
	m_Client_Lobby,
	m_Server_Lobby
};

struct Message
{
	int type;
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

struct Client_InGame_Message
{
	float mouse_pos_x;
	float mouse_pos_y;
	float ball_pos_x;
	float ball_pos_y;
	bool complete_level;
	sf::Int8 strokes;

};

class Packets : public sf::Packet
{
public:
	Packets();
	~Packets();
	
	sf::Packet sendInitialData(Initial_Connect i);
	sf::Packet sendClientLobbyData(Client_Lobby_Message cl);
	sf::Packet sendServerLobbyData(Server_Lobby_Message sl);

	
	sf::Packet sendGameData(sf::Packet packet, Client_InGame_Message cg);

	Message getType(sf::Packet, Message m);
	Initial_Connect recieveInitialData(sf::Packet temp_pack, Initial_Connect i);
	Client_Lobby_Message recieveClientLobbyData(sf::Packet temp_pack, Client_Lobby_Message cl);
	Server_Lobby_Message recieveServerLobbyData(sf::Packet packet, Server_Lobby_Message sl);


private:

	sf::Packet send_packet;

};

