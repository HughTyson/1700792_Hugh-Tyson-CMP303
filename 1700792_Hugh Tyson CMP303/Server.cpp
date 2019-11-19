#include "Server.h"



Server::Server()
{
	port = 53000;
	players_connected = 0;
	max_players = 2;
	listener.listen(port);
	_state = SERVER_LOBBY;
	listener.setBlocking(false);
	start_game = false;
}


Server::~Server()
{
}


void Server::update()
{
	while (true)
	{
		AddPlayer();
	
		RecieveMessage();
	
		SendMessage();
	}
}


void Server::AddPlayer()
{
	

	if (listener.accept(tcpClient[players_connected]) == sf::Socket::Done)
	{
	
		clientInfo[players_connected].ip = tcpClient[players_connected].getRemoteAddress();
		clientInfo[players_connected].player_number = players_connected;
	
		if (players_connected == 0)
		{
			clientInfo[players_connected].host = true;
			
		}
		
		players_connected += 1;

		tcpClient[players_connected].setBlocking(false);
		
	}
}

void Server::RecieveMessage()
{

	for (int i = 0; i < players_connected; i++)
	{
		
		sf::Socket::Status status = tcpClient[i].receive(packets);

		if (status == sf::Socket::Status::Done)
		{
			if (_state == SERVER_LOBBY)
			{
				l_message = packets.recieveLobbyData(packets, l_message);

				std::cout << l_message.ready << "," << l_message.exit << std::endl;

				clientInfo[i].player_ready = l_message.ready;
				clientInfo[i].player_exit = l_message.exit;
			}

		}
	}

}

void Server::SendMessage()
{

	if (_state == SERVER_LOBBY)
	{
		for (int i = 0; i < players_connected; i++)
		{
			
			sl_message.playerCount = players_connected;
			sl_message.player_name[0] = clientInfo[0].player_name;
			sl_message.player_name[1] = clientInfo[1].player_name;
			sl_message.start_game = start_game;

			sf::Packet send_packet;
			send_packet = packets.sendServerLobbyData(sl_message);
			tcpClient[i].send(send_packet);
		}


	}


}

void Server::updateServer()
{

	if (_state == SERVER_LOBBY)
	{
		
	}


}
