#pragma once
#include "Server.h"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "Server_Init.h"
#include "Packets.h"
#include <vector>

struct PlayerInfo
{
	int player_number;
	sf::Vector2f mouse_pos;
	sf::Vector2f ball_position;
	sf::Vector2f ball_velocity;
	int strokes;
	bool level_complete;
	float angle;
	bool is_hitting;
	float last_time;

};

class NetworkingManager
{
public:
	NetworkingManager();
	~NetworkingManager();

	PlayerInfo player_info[2];

	void server_init();

	void lobby_update(bool ready, bool exit);
	bool client_recive();

	bool get_connected() { return connected; };
	void disconnect();

	void game_update();

	int getClientNumber() { return clients_number; };
	
	bool getServerRunning() { return server_running; }	

	int getPing() { return ping; };


	
	//functions for client to server
	bool connect_player(bool host);

	std::vector<PlayerInfo> messages;

	void AddMessage(const PlayerInfo & msg);

	//clock variables

	sf::Clock player_clock;	
	float updateTick;

	sf::Clock game_time;
	float offset_time;
	
	sf::Clock ping_clock;

protected:

	void host_disconnect();

	float ping;
	void ping_request();


	int clients_number;
	int other_number;
	int players_connected;
	sf::Thread network_thread;

	void cleanupgame();

	std::string connecting_ip;

	sf::IpAddress ip;
	bool server_running = false;
	bool connected = false;
	int port = 53000;

	sf::TcpSocket connector;
	sf::UdpSocket udp_connector;
	
	//packet variables
	Message incoming;
	Initial_Connect i_connect;
	Client_Lobby_Message l_message;
	Client_InGame_Message cg_message;

	Server_Lobby_Message sl_message;
	Server_InGame_Message sg_message;

	//time

	bool first_time;


};

