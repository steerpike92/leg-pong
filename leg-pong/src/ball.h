#pragma once

#include "sprite.h"

namespace pong {



class Graphics;
class Leg;
class Opponent;
class Player;



enum BallState {
	BALL_NONE,
	BALL_WALL_COLLISION,
	BALL_LEG_COLLISION,
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