#include "game.h"

#include <SDL.h>

#include <string>
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

	SDL_Rect source_rectangle{ 0,0,200,50 };
	SDL_Point start_position{ 300,350 };
	std::string path = "data/human-leg.png";

	player_ = Sprite(graphics_, path, source_rectangle, start_position);

	graphics_.set_background("data/background4.png");

}



void Game::loop()
{
	//Time variable initialization
	auto last_update_time = SDL_GetTicks();
	unsigned int minimum_frame_time{ 20u };

	while (true) {

		input_.process_events();

		if (input_.quit_flag_ || input_.is_key_pressed(SDL_SCANCODE_ESCAPE))
			return;


		//Time handling
		auto elapsed_time = SDL_GetTicks() - last_update_time;

		//Framerate delay
		if (elapsed_time < minimum_frame_time) {
			auto delay = minimum_frame_time - elapsed_time;
			SDL_Delay(delay);
			elapsed_time = minimum_frame_time;
		}

		last_update_time = SDL_GetTicks();


		update(elapsed_time);

		draw();

	}

}



void Game::update(Uint32 elapsed_time)
{
	player_.update(input_, elapsed_time);
}



void Game::draw()
{
	player_.draw(graphics_);

	graphics_.flip();
}



} // namespace pong