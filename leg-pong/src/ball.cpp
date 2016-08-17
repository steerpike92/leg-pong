#include "ball.h"
#include "graphics.h"
#include "globals.h"
#include "leg.h"
#include <iostream>

namespace pong {



Ball::Ball(){}
Ball::~Ball(){}



Ball::Ball(Graphics& graphics) :
	Sprite(graphics, static_cast<std::string>("data/ball.png"), { 0,0,50,50 }, { 400.0,300.0,0 },0, 1)
{
}



BallState Ball::collision_dectection(Opponent* opponent_leg, Player* player_leg)
{

	if (opponent_refractory == 0) {
		CollisionType collision_type = leg_collision_detection(opponent_leg);
		if (collision_type !=COLLISION_NONE) {
			handle_leg_collision(opponent_leg, collision_type);
			opponent_refractory = k_refactory_frames;
			return BALL_LEG_COLLISION;
		}
	}
	else {
		--opponent_refractory;
	}
	
	if (player_refractory == 0) {
		CollisionType collision_type = leg_collision_detection(player_leg);
		if (collision_type != COLLISION_NONE) {
			handle_leg_collision(player_leg, collision_type);
			player_refractory = k_refactory_frames;
			return BALL_LEG_COLLISION;
		}
	}
	else {
		--player_refractory;
	}

	if (center_position_[0] - radius_ < 0) {//left wall
		velocity_[0] = abs(velocity_[0]);//reflect right
		return BALL_WALL_COLLISION;
	}

	if (center_position_[0] + radius_ > screen_width()) {//right wall
		velocity_[0] = -abs(velocity_[0]);//reflect left
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



CollisionType Ball::leg_collision_detection(Leg* leg)
{
	Eigen::Vector3d relative_position = center_position_ - leg->get_position();
	double radial_distance = relative_position.norm();

	if (radial_distance - radius_ < leg->k_check_radius) {
		double distance = leg->get_distance_to_leg_line(center_position_);
		if (distance < leg->k_distance_from_axis + radius_)
			return COLLISION_STANDARD;
			
	}

	relative_position = center_position_ - leg->get_foot_position();
	radial_distance = relative_position.norm();
	if (radial_distance - radius_ < leg->k_distance_from_axis)
		return COLLISION_FOOT;

	relative_position = center_position_ - leg->get_stub_position();
	radial_distance = relative_position.norm();
	if (radial_distance - radius_ < leg->k_distance_from_axis)
		return COLLISION_STUB;

	return COLLISION_NONE;
}



void Ball::handle_leg_collision(Leg * leg, CollisionType collision_type)
{
	//frame parameters
	Eigen::Vector3d frame_velocity = leg->get_velocity();
	double frame_omega = leg->get_omega();

	//forward tranform
	linear_transform(leg,frame_velocity);
	rotational_transform(leg, frame_omega);

	//calculation
	collision_calculations(leg, collision_type);

	//back transform
	rotational_transform(leg, -frame_omega);
	frame_velocity *= -1;
	linear_transform(leg, frame_velocity);

}



void Ball::linear_transform(Leg * leg, Eigen::Vector3d& frame_velocity)
{
	leg->delta_velocity(-frame_velocity);
	velocity_ -= frame_velocity;
}



void Ball::rotational_transform(Leg * leg, double frame_omega)
{
	Eigen::Vector3d frame_omega_vector = { 0,0,frame_omega };
	Eigen::Vector3d r_ball = center_position_ - leg->center_position_;
	Eigen::Vector3d rot_transform = frame_omega_vector.cross(r_ball);

	leg->delta_omega(-frame_omega);
	velocity_ -= rot_transform;
}

Eigen::Vector3d Ball::get_collision_normal(Leg* leg, CollisionType collision_type) 
{
	Eigen::Vector3d normal;
	switch (collision_type) {
	case(COLLISION_STANDARD):
		normal = leg->get_normal();
		break;
	case(COLLISION_FOOT):
	{
		Eigen::Vector3d r_foot_ball = center_position_ - leg->get_foot_position();
		normal = r_foot_ball.normalized();
	}
	break;
	case(COLLISION_STUB):
	{
		Eigen::Vector3d r_stub_ball = center_position_ - leg->get_stub_position();
		normal = r_stub_ball.normalized();
	}
	break;
	default:
		std::cerr << "Error, Not a collision type" << std::endl;
		exit(EXIT_FAILURE);
	}

	return normal;
}

void Ball::collision_calculations(Leg* leg, CollisionType collision_type)
{

	Eigen::Vector3d r_ball = center_position_ - leg->get_position();
	Eigen::Vector3d normal = get_collision_normal(leg, collision_type);
	Eigen::Vector3d vector_velocity_in = normal * normal.dot(velocity_);
	double sin_theta = r_ball.cross(normal)[2] / r_ball.norm();

	Eigen::Vector3d omega_vector = leg->get_omega_vector();

	double Vin = vector_velocity_in.norm();

	double alpha = mass_/ leg->mass_;
	double beta = pow(r_ball.norm()*sin_theta, 2)/(pow(leg->get_length(),2)/12.0);
	double phi = alpha*(1 + beta);

	double a = 1 + phi;
	double b = -2 * Vin*(phi);
	double c = Vin*Vin*(phi - 1);
	double Vout = quadratic_neg(a, b, c);

	double delta_v = Vout - Vin;

	Eigen::Vector3d delta_vector_velocity = vector_velocity_in.normalized() * delta_v;
	
	//saving values
	velocity_ += delta_vector_velocity;

	leg->delta_velocity(-delta_vector_velocity*(mass_ / leg->mass_));
	//leg->velocity_[1] = v_leg3[1]; // cut y velocity, eventually use to create shakes

	//transfer vertical energy back to ball
	double e_vert = pow(leg->velocity_[1],2)*leg->mass_;
	leg->velocity_[1] = 0;

	double sign = (velocity_[1] > 0) ? 1 : -1;
	velocity_[1] = sign*pow(pow(velocity_[1], 2) + e_vert / mass_, 0.5);

	//save leg spin
	leg->delta_omega( delta_vector_velocity.cross(r_ball)[2]*mass_/ (leg->mass_*pow(leg->get_length(), 2) / 12.0  ));
}



void Ball::update(Uint32 elapsed_time)
{
	Sprite::update(elapsed_time);
}



void Ball::reset()
{
	center_position_[0] = screen_width() / 2;
	center_position_[1] = screen_height() / 2;
	velocity_ = { 0,0,0};
}



void Ball::start()
{
	velocity_ = { 0,400,0 };
}



} // namespace pong