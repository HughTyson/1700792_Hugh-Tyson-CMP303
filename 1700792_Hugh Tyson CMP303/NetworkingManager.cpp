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

bool NetworkingManager::connect_player()
{
	
	sf::Socket::Status status = connector.connect("localhost", port);

	if (status != sf::Socket::Done)
	{
		std::cout << "Error Connecting" << std::endl;
		return false;
	}
	else
	{
		sf::Packet send_packet;
		Packets packet;
	
		send_packet = packet.sendInitialData(i_connect);
	
		connector.send(send_packet);
		send_packet.clear();
	
		return true;
	}

	return false;
}

void NetworkingManager::lobby_update(bool ready, bool exit)
{
	l_message.type = m_Client_Lobby;
	l_message.ready = ready;
	l_message.exit = exit;

	sf::Packet send_packet;
	Packets packet;

	send_packet = packet.sendClientLobbyData(l_message);

	connector.send(send_packet);
	send_packet.clear();

}

bool NetworkingManager::lobby_recive(bool start_game)
{
	Packets recieve_packet;

	sf::Socket::Status status = connector.receive(recieve_packet);

	if (status == sf::Socket::Status::Done)
	{
		incoming = recieve_packet.getType(recieve_packet, incoming);

		if (incoming.type == m_Server_Lobby)
		{
			sl_message = recieve_packet.recieveServerLobbyData(recieve_packet, sl_message);
			
		}
	}
	recieve_packet.clear();

	return sl_message.start_game;

}




