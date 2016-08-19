#include "leg.h"
#include "graphics.h"
#include "input.h"
#include <string>

namespace pong {

Leg::Leg(){}
Leg::~Leg(){}



Leg::Leg(Graphics& graphics, const Eigen::Vector3d& start_center_position, double angle_rad):
	Sprite(graphics, static_cast<std::string>("data/human-leg.png"), { 0,0,200,50 }, start_center_position, angle_rad, 5 )
{
}



void Leg::update(Uint32 elapsed_time)
{
	Sprite::update(elapsed_time);
}



Eigen::Vector3d Leg::get_normal() const
{
	return Eigen::Vector3d{ sin(angle_rad_) , -cos(angle_rad_), 0 };
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



void Leg::push_left(Uint32 elapsed_time){ velocity_[0] -= (k_linear_force / mass_) * elapsed_time / 1000.0; }
void Leg::push_right(Uint32 elapsed_time){ velocity_[0] += (k_linear_force / mass_) * elapsed_time / 1000.0; }
void Leg::torque_up(Uint32 elapsed_time) { angular_velocity_rad_ += (K_torque / mass_) * elapsed_time / 1000.0; }
void Leg::torque_down(Uint32 elapsed_time) { angular_velocity_rad_ -= (K_torque / mass_) * elapsed_time / 1000.0; }

double Leg::get_angular_acceleration() const { return K_torque / mass_;  }
double Leg::get_linear_acceleration() const { return k_linear_force / mass_; }

Player::Player(){}
Player::~Player() {}



Player::Player(Graphics& graphics) :
	Leg(graphics, { 400.0,500.0, 0 }, 0)
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
	angle_rad_ = 0.0;
	angular_velocity_rad_ = 0;

}



Opponent::Opponent(){}
Opponent::~Opponent(){}



Opponent::Opponent(Graphics& graphics) : 
	Leg(graphics, { 350.0, 100.0, 0 }, M_PI )
{
}



void Opponent::AI(const Ball& ball, Uint32 elapsed_time)
{
	lateral_AI(ball, elapsed_time);
	angular_AI(ball, elapsed_time);

	/*if (angular_velocity_rad_ > 0) {
		torque_down(elapsed_time);
	}

	if (angular_velocity_rad_ < 0) {
		torque_up(elapsed_time);
	}
	*/
	


	/*if (both conditions met) :
		do nothing.
	else if (not going in correct direction) :
			accelerate towards destination.
	else (going in correct direction) :
		determine where the stopping point would be in full negative acceleration.
		if (stopping point is beyond destination) :
			negative accelerate.
		else :
			accelerate toward destination*/

	//double working_angle = abs(std::fmod(angle_deg_, M_PI));

	

}



void Opponent::angular_AI(const Ball & ball, Uint32 elapsed_time)
{
	double sign_v = (angular_velocity_rad_ < 0) ? -1 : 1;

	double angular_acceleration = get_angular_acceleration();

	double kill_time = abs(angular_velocity_rad_ / angular_acceleration);
	double kill_sweep = kill_time*angular_velocity_rad_ / 2;
	double norm_finish = kill_time*angular_velocity_rad_ + angle_rad_;
	double kill_finish = kill_sweep + angle_rad_;

	double mod_angle = std::fmod(kill_finish, M_PI);
	if (mod_angle < 0) mod_angle += M_PI;

	double goal_angle = kill_finish;
	if (mod_angle > M_PI / 2)
		goal_angle += M_PI - mod_angle;
	else
		goal_angle -= mod_angle;

	double sign_x = (angle_rad_ > goal_angle) ? -1 : 1;

	enum Action {
		ACTION_NONE,
		ACTION_FORWARD,
		ACTION_REVERSE
	};

	Action action = ACTION_NONE;
	if (sign_v != sign_x) {//going wrong direction
		action = ACTION_REVERSE;
	}
	else {//going in right direction
		if (abs(angle_rad_ - kill_finish) < abs(angle_rad_ - goal_angle))//stopping early
			action = ACTION_NONE;
		else if (abs(angle_rad_ - norm_finish) > abs(angle_rad_ - goal_angle))
			action = ACTION_REVERSE;
	}


	if (action == ACTION_REVERSE) {
		if (sign_v == 1) {//going positive
			torque_down(elapsed_time);
		}
		else {//going negative
			torque_up(elapsed_time);
		}
	}
	else if (action == ACTION_FORWARD) {
		if (sign_v == 1) {//going positive
			torque_up(elapsed_time);
		}
		else {//going negative
			torque_down(elapsed_time);
		}
	}
}



void Opponent::lateral_AI(const Ball & ball, Uint32 elapsed_time)
{
	if (ball.get_position()[0] - center_position_[0]  > 0) {
		push_right(elapsed_time);
	}

	if (ball.get_position()[0] - center_position_[0]  < 0) {
		push_left(elapsed_time);
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
	angle_rad_ = M_PI;
	angular_velocity_rad_ = 0;
}

}// namespace pong