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
	
	sl_message.start_game = false;

	clientInfo[0] = new ClientInfo;
	clientInfo[1] = new ClientInfo;

	clientInfo[0]->player_exit = false;
	clientInfo[1]->player_exit = false;

	clientInfo[0]->player_ready = false;
	clientInfo[1]->player_ready = false;

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

		updateServer();

		if (clientInfo[0]->host == true)
		{
			if (clientInfo[0]->connected == false)
			{
				break;
			}
		}
	}
}


void Server::AddPlayer()
{
	if (listener.accept(tcpClient[players_connected]) == sf::Socket::Done)
	{
		clientInfo[players_connected]->connected = true;
		clientInfo[players_connected]->ip = tcpClient[players_connected].getRemoteAddress();
		clientInfo[players_connected]->player_number = players_connected;
	
		if (players_connected == 0)
		{
			clientInfo[players_connected]->host = true;
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

		//if (status == sf::Socket::Status::Done)
		//{
		//	if (_state == SERVER_LOBBY)
		//	{
		//		cl_message = packets.recieveClientLobbyData(packets, cl_message);

		//		std::cout << clientInfo[i]->player_number << "," << cl_message.ready << "," << cl_message.exit << std::endl;

		//		clientInfo[i]->player_ready = cl_message.ready;

		//		clientInfo[i]->player_exit = cl_message.exit;
		//	}
		//	packets.clear();
		//}

		if (status == sf::Socket::Status::Done)
		{

			incoming = packets.getType(packets, incoming);
			
			switch (incoming.type)
			{
				case m_Client_Lobby:
				{
					if (_state == SERVER_LOBBY)
					{
						cl_message = packets.recieveClientLobbyData(packets, cl_message);

						std::cout << clientInfo[i]->player_number << "," << cl_message.ready << "," << cl_message.exit << std::endl;

						clientInfo[i]->player_ready = cl_message.ready;
					
						clientInfo[i]->player_exit = cl_message.exit;
					}

					//std::cout << clientInfo[i]->player_number << "," << cl_message.ready << "," << cl_message.exit << std::endl;
				}
			default:
				break;
			}

			packets.clear();
		}
	}
}

void Server::SendMessage()
{
	if (_state == SERVER_LOBBY)
	{
		for (int i = 0; i < players_connected; i++)
		{
		
			sl_message.type = m_Server_Lobby;
			sl_message.player_number = clientInfo[i]->player_number;

			sf::Packet send_packet;
			send_packet = packets.sendServerLobbyData(sl_message);
			tcpClient[i].send(send_packet);
			send_packet.clear();
		}
	}
}

void Server::updateServer()
{
	if (_state == SERVER_LOBBY)
	{
		if (clientInfo[0]->player_ready == true && clientInfo[1]->player_ready == true)
		{
			sl_message.start_game = true;
		}

		for (int num = 0; num < players_connected; num++)
		{
			if (clientInfo[num]->player_exit == true)
			{

				tcpClient[num].disconnect();
				clientInfo[num]->connected = false;
				
			}
		}
	}
}

void Server::dissconenctAll()
{
	for (int i = 0; i < players_connected; i++)
	{
		if (clientInfo[i]->host == false)
		{
			tcpClient[i].disconnect();
			clientInfo[i] = NULL;
			delete clientInfo[i];
			
		}
	}
}

void Server::wipeClient(int i)
{
	clientInfo[i] = NULL;
	delete clientInfo[i];

	clientInfo[i] = new ClientInfo;

	clientInfo[0]->player_ready = false;
	clientInfo[1]->player_exit = false;

}
