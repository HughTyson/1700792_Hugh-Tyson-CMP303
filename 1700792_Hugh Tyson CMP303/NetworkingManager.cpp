#include "NetworkingManager.h"



NetworkingManager::NetworkingManager() : network_thread(&server)
{
	updateTick = 0.01;
	sl_message.start_game = false;

	player_info[0].player_number = 0;
	player_info[0].ball_position = sf::Vector2f(90, 500);
	player_info[0].ball_velocity = sf::Vector2f(0.f, 0.f);
	player_info[0].mouse_pos = sf::Vector2f(0, 0);
	player_info[0].strokes = 0;
	player_info[0].level_complete = false;
	player_info[0].angle = 0;
	player_info[0].is_hitting = false;

	player_info[1].player_number = 1;
	player_info[1].ball_position = sf::Vector2f(120, 500);
	player_info[1].mouse_pos = sf::Vector2f(0, 0);
	player_info[1].ball_velocity = sf::Vector2f(0.f, 0.f);
	player_info[1].strokes = 0;
	player_info[1].level_complete = false;
	player_info[1].angle = 0;
	player_info[1].is_hitting = false;
	

	first_time = true;
}

NetworkingManager::~NetworkingManager()
{
}

void NetworkingManager::server_init()
{
	server_running = true;
	network_thread.launch();

	connect_player(true);
}

bool NetworkingManager::connect_player(bool host)
{
	sf::Socket::Status status;
	if (host) //if ocnnectio nis coming fro mpalyer to create server then just conenct ot hte local host
	{
		status = connector.connect("localhost", port);

		std::cout << ip.getLocalAddress() << std::endl; //output hosts local ip address
	}
	else if (!host) //if wanting to connect to another player on a different pc on local network input they're local ip adress
	{
		std::cout << "Please enter ip of server oyu wish to join" << std::endl;
		std::cin >> connecting_ip;

		ip = connecting_ip;

		status = connector.connect(ip, port);
	}


	if (status != sf::Socket::Done) //if not connected return an error as not connected
	{
		std::cout << "Error Connecting" << std::endl;
		return false;
	}
	else //if they are connected
	{
		Packets recieve_packet;
		connector.setBlocking(true); //set client to a blocking socket so it wait until it recieves the first meeasge from the serve
		connected = true;

		sf::Socket::Status status = connector.receive(recieve_packet); //recieve a message fro mthe server
		if (status == sf::Socket::Status::Done) 
		{
			
			
			incoming = recieve_packet.getType(recieve_packet, incoming);

			if (incoming.type == m_Connected)
			{
				
				
				std::cout << "Welcome Player" << std::endl; //output welcome message
				
			}

		}
		connector.setBlocking(false); //set to a non blocking server so ti can recieve messages but not hold up clients program

		return true; //return true as connected to the server
	}

	return false;
}

void NetworkingManager::AddMessage(const PlayerInfo & msg)
{
	messages.push_back(msg); //add latest message to message vector
}

void NetworkingManager::host_disconnect()
{
}

void NetworkingManager::ping_request()
{

	if (ping_clock.getElapsedTime().asSeconds() > 1)
	{
		ping_clock.restart();
		sf::Packet send_packet;
		Packets packets;
		incoming.type = m_Ping;
		incoming.sent_time = game_time.getElapsedTime().asSeconds();

		send_packet = packets.sendPing(incoming);
	
		connector.send(send_packet);
		send_packet.clear();

		//std::cout << "Time sent : " << incoming.sent_time << std::endl;
	}
	
}

void NetworkingManager::cleanupgame()
{
	
	player_info[0].ball_position = sf::Vector2f(90, 500);
	player_info[0].ball_velocity = sf::Vector2f(0.f, 0.f);
	player_info[0].mouse_pos = sf::Vector2f(0, 0);
	player_info[0].strokes = 0;
	player_info[0].level_complete = false;

	player_info[1].ball_position = sf::Vector2f(120, 500);
	player_info[1].mouse_pos = sf::Vector2f(0, 0);
	player_info[1].ball_velocity = sf::Vector2f(0.f, 0.f);
	player_info[1].strokes = 0;
	player_info[1].level_complete = false;


}

void NetworkingManager::lobby_update(bool ready, bool exit)
{

	ping_request();
	
	//this function is used to send the server information about the clients lobby state

	l_message.type = m_Client_Lobby; //send a message of type lobby

	//tells the server if the user is still in the server or if it has exited the server

	l_message.ready = ready;
	l_message.exit = exit;

	//set up the packet that the client is sending to the server
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

	cg_message.velocity_x = player_info[clients_number].ball_velocity.x;
	cg_message.velocity_y = player_info[clients_number].ball_velocity.y;

	cg_message.strokes = player_info[clients_number].strokes;
	cg_message.complete = player_info[clients_number].level_complete;

	cg_message.angle = player_info[clients_number].angle;
	cg_message.is_hitting = player_info[clients_number].is_hitting;
	

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
					game_time.restart();
					cleanupgame();
					//std::cout << game_time.getElapsedTime().asMilliseconds();
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

					player_info[i].ball_velocity.x = sg_message.velocity_x[i];
					player_info[i].ball_velocity.y = sg_message.velocity_y[i];

					player_info[i].angle = sg_message.angle[i];
					player_info[i].is_hitting = sg_message.is_hitting[i];

					player_info[i].last_time = sg_message.sent_time - ping/2;		
				}

				recieve_packet.clear();

				AddMessage(player_info[other_number]);

				if (sg_message.game_complete == true)
				{
					cleanupgame();
				}

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
			case m_Ping:
			{
				
				
				ping = game_time.getElapsedTime().asSeconds() - incoming.sent_time;

				//std::cout << "Time Recieved Server : " << incoming.sent_time << std::endl;

				//std::cout << "Ping : " << ping << std::endl;
			}
			default:
				break;
		}

	}
	else if (status == sf::Socket::Status::Disconnected)
	{
		std::cout << "YOU HAVE BEEN DISCONNENCTED" << std::endl;
		connected = false;
		
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









