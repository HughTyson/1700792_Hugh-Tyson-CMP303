#include "NetworkingManager.h"



NetworkingManager::NetworkingManager() : network_thread(&server)
{
}


NetworkingManager::~NetworkingManager()
{
}

void NetworkingManager::server_init()
{
	server_running = true;
	network_thread.launch();
	i_connect.PlayerName = "Hugh";

	connect_player();
}

void NetworkingManager::connect_player()
{
	
	sf::Socket::Status status = connector.connect("localhost", port);

	if (status != sf::Socket::Done)
	{
		std::cout << "Error" << std::endl;
	}
	else
	{
		sf::Packet send_packet;
		send_packet = packet.sendInitialData(i_connect);
		
		connector.send(send_packet);
	}
}

void NetworkingManager::lobby_update(bool ready, bool exit)
{

	l_message.ready = ready;
	l_message.exit = exit;
	sf::Packet send_packet;

	send_packet = packet.sendClientLobbyData(l_message);

	connector.send(send_packet);

}

void NetworkingManager::lobby_recive(bool* start_game, int* amount_of_players)
{

	sf::Socket::Status status = connector.receive(packet);

	if (status == sf::Socket::Status::Done)
	{
		sl_message = packet.recieveServerLobbyData();
	}




}




