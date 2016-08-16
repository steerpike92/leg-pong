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
	Leg(Graphics& graphics, const Eigen::Vector2d& start_center_position);
	~Leg();

	virtual void update(Uint32 elapsed_time);

private:
	static constexpr double k_check_radius =100.0;
	static constexpr double k_distance_from_axis= 25.0;


	inline Eigen::Vector2d get_normal_2d() const 
	{
		return Eigen::Vector2d{ sin(to_radians(angle_deg_)) , -cos(to_radians(angle_deg_)) };
	}

	inline Eigen::Vector3d get_normal_3d() const 
	{
		return Eigen::Vector3d{ sin(to_radians(angle_deg_)) , -cos(to_radians(angle_deg_)), 0 };
	}

	inline Eigen::Vector3d get_omega_vector() const 
	{
		return Eigen::Vector3d{ 0, 0, angular_velocity_rad_ };
	}

	inline double get_distance_to_leg(const Eigen::Vector2d& other_center) const 
	{
		Eigen::Vector2d r = other_center - center_position_;
		double distance = abs(r.dot(get_normal_2d())); //distance from center to leg line;
		return distance;
	}

	inline double get_length() const 
	{
		return 200.0;
	}


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
private:

};



}// namespace pong