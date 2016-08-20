#pragma once

#include "sprite.h"
#include "ball.h"
#include <Eigen/dense>
#include "globals.h"
#include <cmath>
#include <queue>

namespace pong {

class Input;
class Graphics;



enum LateralForce {
	FORCE_NONE,
	FORCE_RIGHT,
	FORCE_LEFT
};

enum Torque {
	TORQUE_NONE,
	TORQUE_UP,
	TORQUE_DOWN
};



struct Action
{
	LateralForce lateral_force;
	Torque torque;
	unsigned duration;
};



using Plan = std::queue<Action>;


class Leg : public Sprite
{
	friend class Ball;
public:
	Leg();
	Leg(Graphics& graphics, const Eigen::Vector3d& start_center_position, double angle_rad);
	~Leg();

	virtual void update(Uint32 elapsed_time);

protected:
	double get_angular_acceleration() const;
	double get_linear_acceleration() const;

	//basically a command pattern
	Plan action_plan_;

	static constexpr unsigned k_screen_margin{ 100u };

private:
	void execute_plan(Uint32 elapsed_time);
	void execute_action(Action action);

	Eigen::Vector3d get_normal() const;
	double get_distance_to_leg_line(const Eigen::Vector3d& other_center) const;

	inline double get_length() const  {return 200.0;}

	Eigen::Vector3d get_foot_position() const;
	Eigen::Vector3d get_stub_position() const;

	static constexpr double k_check_radius{ 90.0 };
	static constexpr double k_distance_from_axis{ 17.0 };
	static constexpr double k_linear_force{ 8000.0 };
	static constexpr double k_torque{ 16 * M_PI };

	void push_left(Uint32 elapsed_time);
	void push_right(Uint32 elapsed_time);
	void torque_up(Uint32 elapsed_time);
	void torque_down(Uint32 elapsed_time);
};



class Player : public Leg
{
public:
	Player();
	Player(Graphics& graphics);
	~Player();

	void process_input(const Input& input, Uint32 elapsed_time);
	void update(Uint32 elapsed_time);
	
	void reset();

	static constexpr double k_player_y{ static_cast<double>(screen_height() - k_screen_margin) };
	static constexpr double k_player_Xo{ static_cast<double>(screen_width() / 2) };
private:

};



enum Stance {
	STANCE_RECOVER,
	STANCE_ATTACK
};


class Opponent : public Leg
{
public:
	Opponent();
	Opponent(Graphics& graphics);
	~Opponent();

	
	void update(Uint32 elapsed_time);
	void reset();
	void plan(const Ball& ball, Stance stance);

	static constexpr double k_opponent_y{ static_cast<double>(k_screen_margin) };
	static constexpr double k_opponent_Xo{ static_cast<double>(screen_width() / 2) };

private:
	//orients values along Xo to Xr and returns orientation value (-1 if values negated, 1 if unchanged)
	double orient(double &Xo, double &Xr, double &Vo) const;
	Plan attack_plan(const Ball& ball);
	Plan recover_plan(const Ball& ball);
};



}// namespace pong