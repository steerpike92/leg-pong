#include "game.h"

#include <SDL.h>

#include <iostream>

namespace pong {



Game::Game() :
	graphics_(),
	input_()
{
	initialize();
	loop();
}



Game::~Game()
{
}



void Game::initialize()
{

}



void Game::loop()
{


	while (true) {
		input_.process_events();
		if (input_.quit_flag_)
			return;

		
		update();
		draw();

	}

}



void Game::update()
{
	
}



void Game::draw()
{


	graphics_.flip();
}



} // namespace pong