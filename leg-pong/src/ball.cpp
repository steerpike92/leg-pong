#include "ball.h"
#include "graphics.h"
#include "globals.h"
#include "leg.h"
#include <iostream>

namespace pong {



Ball::Ball(){}
Ball::~Ball(){}



Ball::Ball(Graphics& graphics) :
	Sprite(graphics, static_cast<std::string>("data/ball.png"), { 0,0,50,50 }, { 400.0,300.0 },1)
{
}



BallState Ball::collision_dectection(Opponent* opponent_leg, Player* player_leg)
{

	if (opponent_refractory == 0) {
		bool opponent_collision_handled = leg_collision_detection(opponent_leg);
		if (opponent_collision_handled) {
			handle_leg_collision(opponent_leg);
			opponent_refractory = k_refactory_frames;
			return BALL_LEG_COLLISION;
		}
	}
	else {
		--opponent_refractory;
	}
	
	if (player_refractory == 0) {
		bool player_collision_handled = leg_collision_detection(player_leg);
		if (player_collision_handled) {
			handle_leg_collision(player_leg);
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



bool Ball::leg_collision_detection(Leg* leg)
{
	double opponent_radial_distance = (center_position_ - leg->center_position_).norm();
	if (opponent_radial_distance < leg->k_check_radius) {
		
		//for interpolation
		//Eigen::Vector2d r1 = previous_center_position_ - leg->center_position_;
		//Eigen::Vector2d r2 = center_position_-leg->center_position_;

		double distance = leg->get_distance_to_leg(center_position_);

		if (distance < leg->k_distance_from_axis + radius_) {
			return true;
		}
	}
	return false;
}



void Ball::handle_leg_collision(Leg * leg)
{
	linear_transform(leg);
}



void Ball::linear_transform(Leg * leg)
{
	Eigen::Vector2d v_leg = leg->velocity_;

	//forward transform
	leg->velocity_ -= v_leg;
	velocity_ -= v_leg;

	//next stage of computation
	rotational_transform(leg);

	//reverse transform
	leg->velocity_ += v_leg;
	velocity_ += v_leg;

}



void Ball::rotational_transform(Leg * leg)
{
	double w_leg = leg->angular_velocity_rad_;
	Eigen::Vector3d omega_leg = leg->get_omega_vector();

	Eigen::Vector2d r_ball2 = center_position_ - leg->center_position_;
	Eigen::Vector3d r_ball3{ r_ball2[0], r_ball2[1], 0 };	//three dimensional dispacement vector

	Eigen::Vector3d rot_transform3 = omega_leg.cross(r_ball3);
	Eigen::Vector2d rot_transform2{ rot_transform3[0], rot_transform3[1] };

	//forward transform
	leg->angular_velocity_rad_ -= w_leg;
	velocity_ -= rot_transform2;

	//next stage of calculation
	collision_calculations(leg);

	leg->angular_velocity_rad_ += w_leg;
	velocity_ += rot_transform2;
}

void Ball::collision_calculations(Leg *leg)
{

	Eigen::Vector2d r_ball2 = center_position_ - leg->center_position_;
	Eigen::Vector3d r_ball3{ r_ball2[0], r_ball2[1], 0 };	//three dimensional dispacement vector

	Eigen::Vector3d v_ball3{ velocity_[0], velocity_[1], 0 };	//three dimensional ball velocity vector
	
	Eigen::Vector3d normal = leg->get_normal_3d();

	Eigen::Vector3d vector_velocity_in = normal * normal.dot(v_ball3);

	double sin_theta = r_ball3.cross(normal)[2] / r_ball3.norm();


	Eigen::Vector3d v_leg3{leg->velocity_[0], leg->velocity_[1], 0 };	//three dimensional ball velocity vector
	Eigen::Vector3d omega_leg{ 0, 0, leg->angular_velocity_rad_ };	//both should be zero, but decreases coupling if we don't assume.


	double Vin = vector_velocity_in.norm();

	double alpha = mass_/ leg->mass_;
	double beta = pow(r_ball3.norm()*sin_theta, 2)/(pow(leg->get_length(),2)/12.0);
	double phi = alpha*(1 + beta);

	double a = 1 + phi;
	double b = -2 * Vin*(phi);
	double c = Vin*Vin*(phi - 1);
	double Vout = quadratic_neg(a, b, c);


	double delta_v = Vout - Vin;

	Eigen::Vector3d delta_vector_velocity = vector_velocity_in.normalized() * delta_v;
	
	//saving values
	//save ball velocity
	v_ball3 += delta_vector_velocity;
	velocity_[0] = v_ball3[0];
	velocity_[1] = v_ball3[1];

	//save leg velocity
	v_leg3 -= (mass_ / leg->mass_) * delta_vector_velocity;
	leg->velocity_[0] = v_leg3[0]; 
	//leg->velocity_[1] = v_leg3[1]; // cut y velocity, eventually use to create shakes

	//transfer vertical energy back to ball
	double e_vert = pow(v_leg3[1],2)*leg->mass_;
	double sign = (velocity_[1] > 0) ? 1 : -1;
	velocity_[1] = sign*pow(pow(velocity_[1], 2) + e_vert / mass_, 0.5);

	//save leg spin
	leg->angular_velocity_rad_ = delta_vector_velocity.cross(r_ball3)[2]*mass_/ (leg->mass_*pow(leg->get_length(), 2) / 12.0  );
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
	velocity_ = { 0,400 };
}



} // namespace pong