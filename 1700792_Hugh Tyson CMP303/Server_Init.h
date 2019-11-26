#pragma once
#include "Server.h"

static int server()
{
	Server* s;

	s = new Server();

	s->update();

	std::cout << "Server Closed" << std::endl;

	s = NULL;
	delete s;

	return 0;
}