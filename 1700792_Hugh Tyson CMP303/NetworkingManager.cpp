#include "NetworkingManager.h"



NetworkingManager::NetworkingManager() : network_thread(&server)
{
	updateTick = 0.5;
	sl_message.start_game = false;

	player_info[0].player_number = 0;
	player_info[0].ball_position = sf::Vector2f(90, 500);
	player_info[0].mouse_pos = sf::Vector2f(0, 0);
	player_info[0].strokes = 0;

	player_info[1].player_number = 0;
	player_info[1].ball_position = sf::Vector2f(120, 500);
	player_info[1].mouse_pos = sf::Vector2f(0, 0);
	player_info[1].strokes = 0;

	first_time = true;
}


NetworkingManager::~NetworkingManager()
{
}

void NetworkingManager::server_init()
{
	server_running = true;
	network_thread.launch();

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
		Packets recieve_packet;
		connector.setBlocking(true);
		connected = true;

		sf::Socket::Status status = connector.receive(recieve_packet);
		if (status == sf::Socket::Status::Done)
		{
			
			incoming = recieve_packet.getType(recieve_packet, incoming);

			if (incoming.type == m_Connected)
			{
				std::cout << "Welcome Player" << std::endl;
			}

		}
		connector.setBlocking(false);

		return true;
	}

	return false;
}

void NetworkingManager::AddMessage(const PlayerInfo & msg)
{
	messages.push_back(msg);
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

	//std::cout << clients_number << std::endl;

}

void NetworkingManager::game_update()
{
	cg_message.type = m_Client_Game;

	cg_message.player_number = clients_number;

	cg_message.ball_pos_x = player_info[clients_number].ball_position.x;
	cg_message.ball_pos_y = player_info[clients_number].ball_position.y;

	cg_message.mouse_pos_x = player_info[clients_number].mouse_pos.x;
	cg_message.mouse_pos_y = player_info[clients_number].mouse_pos.y;

	cg_message.strokes = player_info[clients_number].strokes;
	cg_message.complete = player_info[clients_number].level_complete;

	sf::Packet send_packet;
	Packets packet;

	send_packet = packet.sendClientGameData(cg_message);

	connector.send(send_packet);
	send_packet.clear();

}


bool NetworkingManager::client_recive()
{
	Packets recieve_packet;

	sf::Socket::Status status = connector.receive(recieve_packet);

	if (status == sf::Socket::Status::Done)
	{
		incoming = recieve_packet.getType(recieve_packet, incoming);

		switch (incoming.type)
		{
			case m_Server_Lobby:
			{
				sl_message = recieve_packet.recieveServerLobbyData(recieve_packet, sl_message);

				player_info[sl_message.player_number].player_number = sl_message.player_number;

				clients_number = sl_message.player_number;
				recieve_packet.clear();

				if (clients_number == 0)
				{
					other_number = 1;
				}
				else if (clients_number == 1)
				{
					other_number = 0;
				}

				if (sl_message.start_game == true)
				{
						player_clock.restart();
				}

				return sl_message.start_game;

				break;
			}
			case m_Server_Game:
			{
				sg_message = recieve_packet.recieveServerInGameData(recieve_packet, sg_message);

				//std::cout << offset_time << std::endl;

				for (int i = 0; i < 2; i++)
				{
					player_info[i].ball_position.x = sg_message.ball_pos_x[i];
					player_info[i].ball_position.y = sg_message.ball_pos_y[i];

					player_info[i].mouse_pos.x = sg_message.mouse_pos_x[i];
					player_info[i].mouse_pos.y = sg_message.mouse_pos_y[i];

					offset_time = sg_message.sent_time - player_clock.getElapsedTime().asSeconds();

					player_info[i].last_time = sg_message.sent_time - offset_time;


					//std::cout << i << " , " << player_info[i].mouse_pos.x << " , " << player_info[i].mouse_pos.y << std::endl;
				}

				recieve_packet.clear();

				AddMessage(player_info[other_number]);

				return sg_message.game_complete;

				break;
			}
			case m_Connected:
			{
				i_connect = recieve_packet.recieveInitialData(recieve_packet, i_connect);

				clients_number = i_connect.PlayerNumber;

				std::cout << clients_number << std::endl;
				break;
			}
			default:
				break;
		}

	}

	recieve_packet.clear();

	return false;

	//std::cout << sl_message.player_number << std::endl;

	
}

void NetworkingManager::disconnect()
{
	connector.disconnect();

	if (server_running == true)
	{
		server_running = false;
	}
}









