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
	execute_plan(elapsed_time);
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
void Leg::torque_up(Uint32 elapsed_time) { angular_velocity_rad_ += (k_torque / mass_) * elapsed_time / 1000.0; }
void Leg::torque_down(Uint32 elapsed_time) { angular_velocity_rad_ -= (k_torque / mass_) * elapsed_time / 1000.0; }

double Leg::get_angular_acceleration() const { return k_torque / mass_;  }
double Leg::get_linear_acceleration() const { return k_linear_force / mass_; }



void Leg::execute_plan(Uint32 elapsed_time)
{
	while (elapsed_time > 0) {

		if (action_plan_.empty()) {//no queued actions
			return;
		}

		Action action = action_plan_.front(); //action not a reference
		auto executed_time{ action.duration };

		if (elapsed_time < executed_time) {
			executed_time = elapsed_time;
			elapsed_time = 0;
			action.duration = executed_time; //update current action
			action_plan_.front().duration -= executed_time;	//update stored action
		}
		else {
			action_plan_.pop();
			elapsed_time -= executed_time;
		}

		execute_action(action);
	}
}


void Leg::execute_action(Action action)
{
	switch (action.lateral_force) {
	case(FORCE_LEFT):
		push_left(action.duration);
		break;
	case(FORCE_RIGHT):
		push_right(action.duration);
		break;
	case(FORCE_NONE):
		break;
	}

	switch (action.torque) {
	case(TORQUE_DOWN):
		torque_down(action.duration);
		break;
	case(TORQUE_UP):
		torque_up(action.duration);
		break;
	case(TORQUE_NONE):
		break;
	}

}


Player::Player(){}
Player::~Player() {}



Player::Player(Graphics& graphics) :
	Leg(graphics, { k_player_Xo, k_player_y, 0 }, 0)
{
}



void Player::process_input(const Input & input, Uint32 elapsed_time)
{
	Action action;
	action.duration = elapsed_time;

	if (input.is_key_held(SDL_SCANCODE_LEFT))
		action.lateral_force = FORCE_LEFT;
	if (input.is_key_held(SDL_SCANCODE_RIGHT))
		action.lateral_force = FORCE_RIGHT;

	if (input.is_key_held(SDL_SCANCODE_A))
		action.torque = TORQUE_DOWN;
	if (input.is_key_held(SDL_SCANCODE_D))
		action.torque = TORQUE_UP;

	Plan new_plan;
	new_plan.emplace(action);

	action_plan_.swap(new_plan);
}



void Player::update(Uint32 elapsed_time)
{
	Leg::update(elapsed_time);
}



void Player::reset()
{
	velocity_ = { 0,0,0 };
	center_position_ = { k_player_Xo, k_player_y, 0 };
	angle_rad_ = 0.0;
	angular_velocity_rad_ = 0;

}



Opponent::Opponent(){}
Opponent::~Opponent(){}



Opponent::Opponent(Graphics& graphics) : 
	Leg(graphics, { k_opponent_Xo, k_opponent_y, 0 }, M_PI )
{
}



void Opponent::plan(const Ball& ball, Stance stance)
{
	switch (stance) {
	case(STANCE_ATTACK):
		action_plan_.swap(attack_plan(ball));
	case(STANCE_RECOVER):
		action_plan_.swap(recover_plan(ball));
	}
}



double Opponent::orient(double & Xo, double & Xr, double & Vo) const
{
	return 0.0;
}

Plan Opponent::attack_plan(const Ball & ball)
{
	Plan plan;

	math::Point point;
	bool incoming=ball.predict_crossing_point(k_opponent_y, point);
	if (!incoming)
		return plan;



	return plan;
}



Plan Opponent::recover_plan(const Ball & ball)
{
	Plan plan;

	math::Point point;
	bool outgoing = ball.predict_crossing_point(Player::k_player_y,point);
	if(!outgoing)
		return plan;



	return plan;
}



void Opponent::update(Uint32 elapsed_time)
{
	Leg::update(elapsed_time);
}



void Opponent::reset()
{
	velocity_ = { 0,0,0 };
	center_position_ = { k_opponent_Xo, k_opponent_y,0 };
	angle_rad_ = M_PI;
	angular_velocity_rad_ = 0;
}

}// namespace pong