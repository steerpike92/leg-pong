#include "leg.h"
#include "graphics.h"
#include "input.h"

#include <string>

namespace pong {

Leg::Leg()
{
}

Leg::Leg(Graphics& graphics, const Eigen::Vector2d& start_position):
	Sprite(graphics, static_cast<std::string>("data/human-leg.png"), { 0,0,200,50 }, start_position )
{

}

Leg::~Leg()
{
}



Player::Player()
{
}

Player::Player(Graphics& graphics) :
	Leg(graphics, { 300.0,475.0 })
{
}



Player::~Player()
{
}

void Player::process_input(const Input & input, Uint32 elapsed_time)
{
	if (input.is_key_held(SDL_SCANCODE_LEFT))
		position_[0] -= elapsed_time / 4.0;
	if (input.is_key_held(SDL_SCANCODE_RIGHT))
		position_[0] += elapsed_time / 4.0;

	if (input.is_key_held(SDL_SCANCODE_A))
		angle_rad_ -= elapsed_time / 10.0;
	if (input.is_key_held(SDL_SCANCODE_D))
		angle_rad_ += elapsed_time / 10.0;
}




Opponent::Opponent()
{
}

Opponent::Opponent(Graphics& graphics) : 
	Leg(graphics, { 300.0, 125.0 })
{

}

Opponent::~Opponent()
{
}



}// namespace pong