#pragma once

#include "sprite.h"
#include "ball.h"
#include <Eigen/dense>
#include "globals.h"
#include <cmath>

namespace pong {

class Input;
class Graphics;

class Leg : public Sprite
{
	friend class Ball;
public:
	Leg();
	Leg(Graphics& graphics, const Eigen::Vector3d& start_center_position, double angle_rad);
	~Leg();

	virtual void update(Uint32 elapsed_time);

protected:
	void push_left(Uint32 elapsed_time);
	void push_right(Uint32 elapsed_time);
	void torque_up(Uint32 elapsed_time);
	void torque_down(Uint32 elapsed_time);

	double get_angular_acceleration() const;
	double get_linear_acceleration() const;

private:
	

	Eigen::Vector3d get_normal() const;
	double get_distance_to_leg_line(const Eigen::Vector3d& other_center) const;

	inline double get_length() const  {return 200.0;}

	Eigen::Vector3d get_foot_position() const;
	Eigen::Vector3d get_stub_position() const;

	static constexpr double k_check_radius{ 90.0 };
	static constexpr double k_distance_from_axis{ 17.0 };
	static constexpr double k_linear_force{ 8000 };
	static constexpr double K_torque{ 16 * M_PI };
	
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
private:

};



class Opponent : public Leg
{
public:
	Opponent();
	Opponent(Graphics& graphics);
	~Opponent();

	
	void update(Uint32 elapsed_time);
	void reset();
	void AI(const Ball& ball, Uint32 elapsed_time);

private:
	void angular_AI(const Ball& ball, Uint32 elapsed_time);
	void lateral_AI(const Ball& ball, Uint32 elapsed_time);
};



}// namespace pong