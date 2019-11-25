#include "Packets.h"



Packets::Packets()
{
}


Packets::~Packets()
{
}



sf::Packet Packets::sendInitialData(Initial_Connect i)
{
	send_packet.clear();
	return send_packet << i.PlayerName;
}

sf::Packet Packets::sendClientLobbyData(Client_Lobby_Message cl)
{
	send_packet.clear();
	return send_packet << cl.type << cl.ready << cl.exit;
}

sf::Packet Packets::sendServerLobbyData(Server_Lobby_Message sl)
{
	send_packet.clear();
	return send_packet << sl.type <<sl.start_game;
}

Message Packets::getType(sf::Packet temp_packet, Message m)
{
	temp_packet >> m.type;
	return m;
}

Initial_Connect Packets::recieveInitialData(sf::Packet temp_pack,Initial_Connect i)
{
	temp_pack >> i.PlayerName;
	return i;
}

Client_Lobby_Message Packets::recieveClientLobbyData(sf::Packet temp_pack, Client_Lobby_Message cl)
{
	temp_pack >> cl.type >> cl.ready >> cl.exit;
	return cl;
}

Server_Lobby_Message Packets::recieveServerLobbyData(sf::Packet temp_packet, Server_Lobby_Message sl)
{
	temp_packet >> sl.type >> sl.start_game;
	return sl;
}

