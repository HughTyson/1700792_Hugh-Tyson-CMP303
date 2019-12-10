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
	close_server = false;
	
	sl_message.start_game = false;
	sg_message.game_complete = false;

	clientInfo[0] = new ClientInfo;
	clientInfo[1] = new ClientInfo;

	clientInfo[0]->ball_pos = sf::Vector2f(90, 500);
	clientInfo[1]->ball_pos = sf::Vector2f(120, 500);

	clientInfo[0]->mouse_pos = sf::Vector2f(0, 0);
	clientInfo[1]->mouse_pos = sf::Vector2f(0, 0);

	for (int i = 0; i < 2; i++)
	{
		clientInfo[i]->player_number = i;
		clientInfo[i]->connected = false;
		clientInfo[i]->port = 0;
		clientInfo[i]->host = false;
		clientInfo[i]->strokes = 0;
		clientInfo[i]->player_ready = false;
		clientInfo[i]->player_exit = false;
		clientInfo[i]->level_complete = false;
		just_joined[i] = false;
		clientInfo[i]->angle = 0;
		clientInfo[i]->is_hitting = false;
	}

	clientUpdateTime = 0.01;
	finish_game = false;


	m_Time = 0.f;
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

				dissconenctAll();

				std::cout << "Closing" << std::endl;
				listener.close();
				
				
				break;
			}
		}
	}
}

void Server::cleanupLobby()
{

	//function thats used to change varibles used in lobby back to inital state

	sl_message.start_game = false;

	for (int i = 0; i < 2; i++)
	{

		clientInfo[i]->level_complete = false;
		clientInfo[i]->player_ready = false;
		sl_message.start_game = false;

	}


}

void Server::cleanupGame()
{
	for (int i = 0; i < 2; i++)
	{
		clientInfo[i]->strokes = 0;
		clientInfo[i]->player_ready = false;
		clientInfo[i]->player_exit = false;
		clientInfo[i]->level_complete = false;
		clientInfo[i]->ball_velocity = sf::Vector2f(0.f, 0.f);
	}

	clientInfo[0]->ball_pos = sf::Vector2f(90, 500);
	clientInfo[1]->ball_pos = sf::Vector2f(120, 500);

	clientInfo[0]->mouse_pos = sf::Vector2f(0, 0);
	clientInfo[1]->mouse_pos = sf::Vector2f(0, 0);

	sl_message.start_game = false;
	sg_message.game_complete = false;
}


void Server::AddPlayer()
{
	if (players_connected < 2)
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

			tcpClient[players_connected].setBlocking(false);

			just_joined[players_connected] = true;

			players_connected += 1;
		}
	}
	
}

void Server::RecieveMessage()
{
	for (int i = 0; i < players_connected; i++)
	{
		
		sf::Socket::Status status = tcpClient[i].receive(packets);

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

						clientInfo[i]->player_ready = cl_message.ready;
					
						clientInfo[i]->player_exit = cl_message.exit;
					}
					break;
				}

				case m_Client_Game:
				{
					if (_state == SERVER_GAME)
					{
						cg_message = packets.recieveClientInGameData(packets, cg_message);

						clientInfo[i]->mouse_pos = sf::Vector2f(cg_message.mouse_pos_x, cg_message.mouse_pos_y);
						clientInfo[i]->ball_pos = sf::Vector2f(cg_message.ball_pos_x, cg_message.ball_pos_y);
						clientInfo[i]->ball_velocity = sf::Vector2f(cg_message.velocity_x, cg_message.velocity_y);
						clientInfo[i]->strokes = cg_message.strokes;
						clientInfo[i]->angle = cg_message.angle;
						clientInfo[i]->is_hitting = cg_message.is_hitting;
						clientInfo[i]->level_complete = cg_message.complete;
						
					}
					break;
				}

				case m_Ping:
				{
					sf::Packet send_packet;
					incoming.type = m_Ping;
					send_packet = packets.sendPing(incoming);

					tcpClient[i].send(send_packet);

					incoming.sent_time = 0.f;
				}
			default:
				break;
			}

			packets.clear();
		}
		if (status == sf::Socket::Disconnected)
		{
			clientInfo[i]->player_exit = true;
		}
	}
}

void Server::SendMessage()
{

	float timeSinceLastUpdate = networkUpdateTimer.getElapsedTime().asSeconds();

	if (timeSinceLastUpdate >= clientUpdateTime)
	{
		networkUpdateTimer.restart();

		if (_state == SERVER_LOBBY)
		{

			for (int i = 0; i < players_connected; i++)
			{
					if (just_joined[i] == true)
					{
						sf::Packet send_packet;
						i_connect.type = m_Connected;
						i_connect.PlayerNumber = players_connected;

						send_packet = packets.sendInitialData(i_connect);
						tcpClient[i].send(send_packet);
						send_packet.clear();

						just_joined[i] = false;
						continue;
					}
				sl_message.type = m_Server_Lobby;
				sl_message.player_number = clientInfo[i]->player_number;



				//std::cout << sl_message.start_game << std::endl;

				sf::Packet send_packet;
				send_packet = packets.sendServerLobbyData(sl_message);
				tcpClient[i].send(send_packet);
				send_packet.clear();			
				

			}				
			
			if (sl_message.start_game == true)
			{

				_state = SERVER_GAME;
				sl_message.start_game = false;
				cleanupLobby();
				

			}
		}
		else if (_state == SERVER_GAME)
		{


			sg_message.type = m_Server_Game;
			sg_message.sent_time = gameTime.getElapsedTime().asSeconds();

			for (int i = 0; i < players_connected; i++) //load data into struct
			{

				sg_message.player_number[i] = clientInfo[i]->player_number;

				sg_message.ball_pos_x[i] = clientInfo[i]->ball_pos.x;
				sg_message.ball_pos_y[i] = clientInfo[i]->ball_pos.y;

				sg_message.mouse_pos_x[i] = clientInfo[i]->mouse_pos.x;
				sg_message.mouse_pos_y[i] = clientInfo[i]->mouse_pos.y;

				sg_message.velocity_x[i] = clientInfo[i]->ball_velocity.x;
				sg_message.velocity_y[i] = clientInfo[i]->ball_velocity.y;

				sg_message.strokes[i] = clientInfo[i]->strokes;

				sg_message.angle[i] = clientInfo[i]->angle;
				sg_message.is_hitting[i] = clientInfo[i]->is_hitting;

			}

			sf::Packet send_packet;
			send_packet = packets.sendServerGameData(sg_message);

			tcpClient[0].send(send_packet);
			tcpClient[1].send(send_packet);				
			
			if (sg_message.game_complete == true)
			{
				_state = SERVER_LOBBY;
				sg_message.game_complete = false;
				cleanupGame();
			}

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
			gameTime.restart();
			return;
		}

		for (int num = 0; num < players_connected; num++)
		{
			//check if any of the clients want to exit the server
			if (clientInfo[num]->player_exit == true)
			{
				tcpClient[num].disconnect(); //disconnect the tcp socket for that client
				clientInfo[num]->connected = false; 
				players_connected -= 1; //subtract the amount of clients connected

				if (!clientInfo[num]->host) //if the clienet isn't the server clear that clients information
				{
					wipeClient(num);
				}
				
			}
		}
	}
	else if (_state == SERVER_GAME)
	{

		if (clientInfo[0]->level_complete == true && clientInfo[1]->level_complete == true)
		{
			sg_message.game_complete = true;
			return;
		}

		for (int num = 0; num < players_connected; num++)
		{
			//check if any of the clients want to exit the server
			if (clientInfo[num]->player_exit == true)
			{
				tcpClient[num].disconnect(); //disconnect the tcp socket for that client
				clientInfo[num]->connected = false;
				players_connected -= 1; //subtract the amount of clients connected

				if (!clientInfo[num]->host) //if the clienet isn't the server clear that clients information
				{
					wipeClient(num);
				}

				std::cout << "Player Disconnected. Going back to Lobby" << std::endl;
				sg_message.game_complete = true;
			}
		}

	}
}

void Server::dissconenctAll()
{
	for (int i = 0; i < players_connected; i++)
	{
		tcpClient[i].disconnect();
		clientInfo[i] = NULL;
		delete clientInfo[i];
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
