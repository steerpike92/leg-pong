#include "leg.h"
#include "graphics.h"
#include "input.h"
#include <string>

namespace pong {

Leg::Leg(){}
Leg::~Leg(){}



Leg::Leg(Graphics& graphics, const Eigen::Vector3d& start_center_position):
	Sprite(graphics, static_cast<std::string>("data/human-leg.png"), { 0,0,200,50 }, start_center_position, 5 )
{
}



void Leg::update(Uint32 elapsed_time)
{
	Sprite::update(elapsed_time);
}



Eigen::Vector3d Leg::get_normal() const
{
	return Eigen::Vector3d{ sin(to_radians(angle_deg_)) , -cos(to_radians(angle_deg_)), 0 };
}

double Leg::get_distance_to_leg_line(const Eigen::Vector3d& other_center) const
{
	Eigen::Vector3d r = other_center - center_position_;
	double distance = abs(r.dot(get_normal())); //distance from center to leg line;
	return distance;
}

Eigen::Vector3d Leg::get_foot_position() const 
{
	auto normal = get_normal();
	Eigen::Vector3d h_sol = { normal[1], -normal[0], 0 };
	return center_position_ + h_sol * 90;
}

Eigen::Vector3d Leg::get_stub_position() const 
{
	auto normal = get_normal();
	Eigen::Vector3d h_sol = { normal[1], -normal[0], 0 };
	return center_position_ - h_sol * 90;
}



void Leg::push_left(Uint32 elapsed_time){ velocity_[0] -= (4000 / mass_) * elapsed_time / 1000.0; }
void Leg::push_right(Uint32 elapsed_time){ velocity_[0] += (4000 / mass_) * elapsed_time / 1000.0; }
void Leg::torque_up(Uint32 elapsed_time) { angular_velocity_rad_ += (16 * M_PI / mass_) * elapsed_time / 1000.0; }
void Leg::torque_down(Uint32 elapsed_time) { angular_velocity_rad_ -= (16 * M_PI / mass_) * elapsed_time / 1000.0; }



Player::Player(){}
Player::~Player() {}



Player::Player(Graphics& graphics) :
	Leg(graphics, { 400.0,500.0, 0 })
{
}



void Player::process_input(const Input & input, Uint32 elapsed_time)
{
	if (input.is_key_held(SDL_SCANCODE_LEFT))
		push_left(elapsed_time);
	if (input.is_key_held(SDL_SCANCODE_RIGHT))
		push_right(elapsed_time);
	if (input.is_key_held(SDL_SCANCODE_A))
		torque_down(elapsed_time);
	if (input.is_key_held(SDL_SCANCODE_D))
		torque_up(elapsed_time);
}



void Player::update(Uint32 elapsed_time)
{
	Leg::update(elapsed_time);
}


void Player::reset()
{
	velocity_ = { 0,0,0 };
	center_position_ = { 400.0,500.0, 0 };
	angle_deg_ = 0.0;
	angular_velocity_rad_ = 0;

}


Opponent::Opponent(){}
Opponent::~Opponent(){}



Opponent::Opponent(Graphics& graphics) : 
	Leg(graphics, { 400.0, 100.0, 0 })
{
	angle_deg_ = 180;
}


void Opponent::AI(const Ball& ball, Uint32 elapsed_time)
{

	//double working_angle = abs(std::fmod(angle_deg_, 180.0));
	
	if (angular_velocity_rad_ > 0) {
		torque_down(elapsed_time);
	}

	if (angular_velocity_rad_ < 0) {
		torque_up(elapsed_time);
	}





}


void Opponent::update(Uint32 elapsed_time)
{
	Leg::update(elapsed_time);
}

void Opponent::reset()
{
	velocity_ = { 0,0,0 };
	center_position_ = { 400.0,100.0,0 };
	angle_deg_ = 180.0;
	angular_velocity_rad_ = 0;
}

}// namespace pong