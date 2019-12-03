#include "Packets.h"



Packets::Packets()
{
}


Packets::~Packets()
{
}

//initial connect packet unpacking and packing

sf::Packet Packets::sendInitialData(Initial_Connect i)
{
	send_packet.clear();
	return send_packet << i.type <<  i.PlayerNumber;
}

Initial_Connect Packets::recieveInitialData(sf::Packet temp_pack,Initial_Connect i)
{
	temp_pack >> i.type >> i.PlayerNumber;
	return i;
}


//Lobby packet unpacking and packing

Client_Lobby_Message Packets::recieveClientLobbyData(sf::Packet temp_pack, Client_Lobby_Message cl)
{
	temp_pack >> cl.type >> cl.ready >> cl.exit;
	return cl;
}

Server_Lobby_Message Packets::recieveServerLobbyData(sf::Packet temp_packet, Server_Lobby_Message sl)
{
	temp_packet >> sl.type >>  sl.start_game >> sl.player_number;
	return sl;
}



sf::Packet Packets::sendServerLobbyData(Server_Lobby_Message sl)
{
	send_packet.clear();
	return send_packet << sl.type  << sl.start_game << sl.player_number;
}

sf::Packet Packets::sendClientLobbyData(Client_Lobby_Message cl)
{
	send_packet.clear();
	return send_packet << cl.type  << cl.ready << cl.exit;
}

//functions used to pack and unpack level packets

sf::Packet Packets::sendClientGameData(Client_InGame_Message cg)
{
	send_packet.clear();
	return send_packet << cg.type << cg.sent_time << cg.player_number << cg.mouse_pos_x << cg.mouse_pos_y << cg.ball_pos_x << cg.ball_pos_y << cg.strokes << cg.complete;
}

Client_InGame_Message Packets::recieveClientInGameData(sf::Packet temp_packet, Client_InGame_Message cg)
{
	
	temp_packet >> cg.type >> cg.sent_time >> cg.player_number >> cg.mouse_pos_x >> cg.mouse_pos_y >> cg.ball_pos_x >> cg.ball_pos_y >> cg.strokes >> cg.complete;
	return cg;
}



sf::Packet Packets::sendServerGameData(Server_InGame_Message sg)
{
	send_packet.clear();

	return send_packet << sg.type << sg.sent_time << sg.player_number[0] << sg.ball_pos_x[0] << sg.ball_pos_y[0] << sg.mouse_pos_x[0] << sg.mouse_pos_y[0] << sg.strokes[0] 
		<< sg.player_number[1] << sg.ball_pos_x[1] << sg.ball_pos_y[1] << sg.mouse_pos_x[1] << sg.mouse_pos_y[1] << sg.strokes[1]
		<< sg.game_complete;
}

Server_InGame_Message Packets::recieveServerInGameData(sf::Packet temp_packet, Server_InGame_Message sg)
{

	temp_packet >> sg.type >> sg.sent_time >> sg.player_number[0] >> sg.ball_pos_x[0] >> sg.ball_pos_y[0] >> sg.mouse_pos_x[0] >> sg.mouse_pos_y[0] >> sg.strokes[0]
		>> sg.player_number[1] >> sg.ball_pos_x[1] >> sg.ball_pos_y[1] >> sg.mouse_pos_x[1] >> sg.mouse_pos_y[1] >> sg.strokes[1]
		>> sg.game_complete;
	return sg;
}


//unpack what type of message has been sent
Message Packets::getType(sf::Packet temp_packet, Message m)
{
	temp_packet >> m.type;
	return m;
}





