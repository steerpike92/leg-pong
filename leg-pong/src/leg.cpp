#include "leg.h"
#include "graphics.h"
#include "input.h"

#include <string>

namespace pong {

Leg::Leg(){}
Leg::~Leg(){}



Leg::Leg(Graphics& graphics, const Eigen::Vector2d& start_center_position):
	Sprite(graphics, static_cast<std::string>("data/human-leg.png"), { 0,0,200,50 }, start_center_position, 5 )
{
}



void Leg::update(Uint32 elapsed_time)
{
	Sprite::update(elapsed_time);
}






Player::Player(){}
Player::~Player() {}



Player::Player(Graphics& graphics) :
	Leg(graphics, { 400.0,500.0 })
{
}



void Player::process_input(const Input & input, Uint32 elapsed_time)
{
	if (input.is_key_held(SDL_SCANCODE_LEFT))
		velocity_[0] -= 500 * elapsed_time/1000.0;
	if (input.is_key_held(SDL_SCANCODE_RIGHT))
		velocity_[0] += 500 * elapsed_time / 1000.0;

	if (input.is_key_held(SDL_SCANCODE_A))
		angular_velocity_ -= 120 * elapsed_time / 1000.0;
	if (input.is_key_held(SDL_SCANCODE_D))
		angular_velocity_ += 120 * elapsed_time / 1000.0;
}



void Player::update(Uint32 elapsed_time)
{
	Leg::update(elapsed_time);
}





Opponent::Opponent(){}
Opponent::~Opponent(){}



Opponent::Opponent(Graphics& graphics) : 
	Leg(graphics, { 400.0, 100.0 })
{
	angle_deg_ = 180;
}



void Opponent::update(Uint32 elapsed_time)
{
	Leg::update(elapsed_time);
}



}// namespace pong