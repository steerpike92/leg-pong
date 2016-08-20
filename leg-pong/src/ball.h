#pragma once

#include "sprite.h"
#include "globals.h"

namespace pong {


class Graphics;
class Leg;
class Opponent;
class Player;



enum BallState {
	BALL_NONE,
	BALL_WALL_COLLISION,
	BALL_PLAYER_COLLISION,
	BALL_OPPONENT_COLLISION,
	BALL_PLAYER_SCORE,
	BALL_OPPONENT_SCORE
};

enum CollisionType {
	COLLISION_NONE,
	COLLISION_STANDARD,
	COLLISION_FOOT,
	COLLISION_STUB
};


class Ball : public Sprite
{
public:
	Ball();
	Ball(Graphics& graphics);
	~Ball();

	BallState collision_dectection(Opponent* opponent_leg, Player* player_leg);
	void update(Uint32 elapsed_time);
	void reset();
	void start();

	//Predict space time point (point) at which the ball crosses the line y=Y;
	//Returns false if ball isn't headed in that direction, true if it is.
	bool predict_crossing_point(double Y, math::Point& point) const;

private:
	double radius_ = 25.0;

	static constexpr int k_refactory_frames = 10;
	int player_refractory = 0;
	int opponent_refractory = 0;
	
	CollisionType leg_collision_detection(Leg* leg);
	void handle_leg_collision(Leg* leg, CollisionType collision_type);
	void linear_transform(Leg* leg, Eigen::Vector3d& frame_velocity);
	void rotational_transform(Leg* leg, double frame_omega);
	Eigen::Vector3d get_collision_normal(Leg* leg, CollisionType collision_type);
	void collision_calculations(Leg* leg, CollisionType collision_type);
};


} // namespace pong