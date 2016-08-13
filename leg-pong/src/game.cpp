#include "game.h"

#include <SDL.h>
#include <Eigen/dense>

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
	player_ = Player(graphics_);
	opponent_ = Opponent(graphics_);
	ball_ = Ball(graphics_);

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
	player_.process_input(input_, elapsed_time);
	player_.update(elapsed_time);
	opponent_.update(elapsed_time);
	ball_.update(elapsed_time);
}



void Game::draw()
{
	player_.draw(graphics_);
	opponent_.draw(graphics_);
	ball_.draw(graphics_);

	graphics_.flip();
}



} // namespace pong