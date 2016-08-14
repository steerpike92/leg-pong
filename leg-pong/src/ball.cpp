#include "ball.h"
#include "graphics.h"
#include "globals.h"
#include "leg.h"

namespace pong {



Ball::Ball(){}
Ball::~Ball(){}



Ball::Ball(Graphics& graphics) :
	Sprite(graphics, static_cast<std::string>("data/ball.png"), { 0,0,50,50 }, { 400.0,300.0 },1)
{
}









BallState Ball::collision_dectection(Opponent* opponent_leg, Player* player_leg)
{

	if (leg_collision_detection(opponent_leg))
		return BALL_LEG_COLLISION;

	if (leg_collision_detection(player_leg))
		return BALL_LEG_COLLISION;

	if (center_position_[0] - radius_ < 0) {//left wall
		return BALL_WALL_COLLISION;
	}
	if (center_position_[0] + radius_ > screen_width()) {//right wall

		return BALL_WALL_COLLISION;
	}
	if (center_position_[1]  < 0) {
		return BALL_PLAYER_SCORE;
	}
	if (center_position_[1]  > screen_height()) {
		return BALL_OPPONENT_SCORE;
	}
	return BALL_NONE;
}



bool Ball::leg_collision_detection(Leg* leg)
{
	double opponent_radial_distance = (center_position_ - leg->center_position_).norm();
	if (opponent_radial_distance < leg->k_check_radius) {
		double theta_rad = to_radians(leg->angle_deg_);
		Eigen::Vector2d n{ sin(theta_rad) , -cos(theta_rad) };
		Eigen::Vector2d Q_P = center_position_-leg->center_position_;

		double distance = abs(Q_P.dot(n)); //distance from ball to leg line;

		if (distance < leg->k_distance_from_axis + radius_) {
			handle_leg_collision(leg);
			velocity_ = -velocity_;
			return true;
		}
	}

	return false;
}

void Ball::handle_leg_collision(Leg * leg)
{

}



void Ball::update(Uint32 elapsed_time)
{
	Sprite::update(elapsed_time);
}



void Ball::reset()
{
	center_position_[0] = screen_width() / 2;
	center_position_[1] = screen_height() / 2;
	velocity_ = { 0,0 };
}



void Ball::start()
{
	velocity_ = { 0,500 };
}

} // namespace pong