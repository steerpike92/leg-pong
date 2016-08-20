#include "game.h"
#include "sprite.h"

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

	last_update_time_ = SDL_GetTicks();

	//audio_.playMusic();

}



void Game::loop()
{
	while (true) {

		input_.process_events();

		if (input_.quit_flag_ || input_.is_key_pressed(SDL_SCANCODE_ESCAPE))
			return;

		if (game_state_ == GAME_RESET) {
			if (input_.is_key_pressed(SDL_SCANCODE_SPACE)){
				game_state_ = GAME_RUNNING;
				ball_.start();
			}
		}

		if (input_.is_key_pressed(SDL_SCANCODE_R)) {
			reset();
		}



		//Time handling and Framerate delay
		unsigned elapsed_time = delay_timer();
		
		update(elapsed_time);

		draw();
	}
}



unsigned Game::delay_timer()
{
	unsigned elapsed_time = SDL_GetTicks() - last_update_time_;
	if (elapsed_time < k_minimum_frame_time_) {
		auto delay = k_minimum_frame_time_ - elapsed_time;
		SDL_Delay(delay);
		elapsed_time = k_minimum_frame_time_;
	}
	last_update_time_ = SDL_GetTicks();

	elapsed_time = std::min(k_maximum_frame_time_, elapsed_time);

	return elapsed_time;
}



void Game::update(Uint32 elapsed_time)
{
	ball_.update(elapsed_time);

	BallState ball_state=ball_.collision_dectection(&opponent_, &player_);

	switch (ball_state) {
	case(BALL_NONE): 
		break;
	case(BALL_WALL_COLLISION):
		audio_.playSound(SOUND_BA);
		break;
	case(BALL_PLAYER_COLLISION): 
		audio_.playSound(SOUND_SPIT);
		opponent_.plan(ball_, STANCE_ATTACK);
		break;
	case(BALL_OPPONENT_COLLISION):
		audio_.playSound(SOUND_SPIT);
		opponent_.plan(ball_, STANCE_RECOVER);
		break;
	case(BALL_PLAYER_SCORE): 
		score_++;
		reset();
		game_state_ = GAME_RESET;
		audio_.playSound(SOUND_BA);
		break;
	case(BALL_OPPONENT_SCORE): 
		score_--;
		reset();
		game_state_ = GAME_RESET;
		audio_.playSound(SOUND_BA);
		break;
	}

	player_.process_input(input_, elapsed_time);
	player_.update(elapsed_time);

	opponent_.update(elapsed_time);
}



void test(Game* game)
{
	Ball pseudo_ball(game->graphics_);
	math::Point point;

	if (game->ball_.predict_crossing_point(game->player_.k_player_y, point)) {
		pseudo_ball.center_position_ = { point.x,point.y,0 };
		pseudo_ball.draw(game->graphics_);
	}

	if (game->ball_.predict_crossing_point(game->opponent_.k_opponent_y, point)) {
		pseudo_ball.center_position_ = { point.x,point.y,0 };
		pseudo_ball.draw(game->graphics_);
	}
}


void Game::draw()
{
	player_.draw(graphics_);
	opponent_.draw(graphics_);
	ball_.draw(graphics_);

	test(this);
	
	graphics_.flip();
}



void Game::reset()
{
	ball_.reset();
	player_.reset();
	opponent_.reset();
	game_state_ = GAME_RESET;
}



} // namespace pong