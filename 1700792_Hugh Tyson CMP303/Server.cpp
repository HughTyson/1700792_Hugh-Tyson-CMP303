#include "Server.h"



Server::Server()
{
	port = 53000;
	players_connected = 0;
	max_players = 2;
	listener.listen(port);
	_state = SERVER_LOBBY;
}


Server::~Server()
{
}


void Server::update()
{
	while (true)
	{
		
		if (_state == SERVER_LOBBY)
		{
			AddPlayer();
		}
			
		RecieveMessage();

		SendMessage();
	}

}


void Server::AddPlayer()
{
	listener.setBlocking(false);
	
	//tcpClient.setBlocking(false);

	if (listener.accept(tcpClient[players_connected]) == sf::Socket::Done)
	{
		std::cout << "connection from " << tcpClient[players_connected].getRemoteAddress() << std::endl;
		temp_info.ip = tcpClient[players_connected].getRemoteAddress();

		if (players_connected == 0)
		{
			temp_info.host == true;
		}


		temp_info.player_number = players_connected + 1;
		players_connected += 1;
		clientInfo.push_back(temp_info);

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
				//i_connect = packets.recieveInitialData(packets,i_connect);

				//std::cout << i_connect.PlayerName << std::endl;

				l_message = packets.recieveLobbyData(packets, l_message);

				std::cout << l_message.ready << "," << l_message.exit << std::endl;
			}

		}
	}

}

void Server::SendMessage()
{

	if (_state == SERVER_LOBBY)
	{

	}


}
