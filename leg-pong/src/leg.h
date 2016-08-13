#pragma once

#include "sprite.h"


namespace pong {

class Input;
class Graphics;

class Leg : public Sprite
{
public:
	Leg();
	Leg(Graphics& graphics, const Eigen::Vector2d& start_position);
	~Leg();

	virtual void update(Uint32 elapsed_time);

private:
	 

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