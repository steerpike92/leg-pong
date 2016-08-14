#pragma once

#include "sprite.h"
#include "ball.h"

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
};



class Player : public Leg
{
public:
	Player();
	Player(Graphics& graphics);
	~Player();

	void process_input(const Input& input, Uint32 elapsed_time);
	void update(Uint32 elapsed_time);

private:

};



class Opponent : public Leg
{
public:
	Opponent();
	Opponent(Graphics& graphics);
	~Opponent();

	void update(Uint32 elapsed_time);
private:

};



}// namespace pong