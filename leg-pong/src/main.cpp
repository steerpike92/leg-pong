#include "game.h"

#include <SDL.h>

#include <iostream>
#include <fstream>

int main(int argc, char* args[])
{
	//redirect cerr to error-log.txt file
	std::ofstream err("../error-log.txt");
	std::cerr.rdbuf(err.rdbuf());
	
	pong::Game game;
	return 0;
}
