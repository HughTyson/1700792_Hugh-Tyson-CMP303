#include <iostream>
#include "SFML/Network.hpp"

int main()
{

	bool server_on = true;
	std::cout << "Server Running" << std::endl;

	sf::UdpSocket socket;
	sf::SocketSelector selector;

	while (server_on)
	{
		if (selector.wait())
		{
			if (socket.bind(5400) != sf::Socket::Done)
			{
				std::cout << "Error" << std::endl;
			}
		}

	}


}