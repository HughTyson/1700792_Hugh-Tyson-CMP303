#include "Packets.h"



Packets::Packets()
{
}


Packets::~Packets()
{
}

sf::Packet Packets::sendInitialData(Initial_Connect i)
{
	return temp_packet << i.PlayerName;
}

sf::Packet Packets::sendLobbyData(sf::Packet packet, Client_Lobby_Message cl)
{
	return temp_packet << cl.ready << cl.exit;
}

Initial_Connect Packets::recieveInitialData(sf::Packet temp_pack,Initial_Connect i)
{
	temp_pack >> i.PlayerName;
	return i;
}

Client_Lobby_Message Packets::recieveLobbyData(sf::Packet temp_pack, Client_Lobby_Message cl)
{
	temp_pack >> cl.ready >> cl.exit;
	return cl;
}

