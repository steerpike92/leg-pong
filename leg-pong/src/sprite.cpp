#include "sprite.h"

#include "graphics.h"
#include "input.h"
#include "globals.h"

namespace pong {



Sprite::Sprite(){}
Sprite::~Sprite(){}



Sprite::Sprite(Graphics& graphics, const std::string& file_path, SDL_Rect source_rectangle, const Eigen::Vector3d &center_position, double mass) :
	file_path_(file_path),
	source_rectangle_(source_rectangle),
	center_position_(center_position),
	angle_deg_(0),
	mass_(mass)
{
	graphics.load_image(file_path_);
}



void Sprite::update(Uint32 elapsed_time)
{
	previous_center_position_ = center_position_;
	center_position_ += velocity_* elapsed_time / 1000.0;

	previous_angle_deg_ = angle_deg_;
	angle_deg_ += (to_degrees(angular_velocity_rad_)) * elapsed_time / 1000.0;
}



void Sprite::draw(Graphics & graphics) const
{
	Eigen::Vector2i corner_position = get_corner_position();
	SDL_Rect destination_rectangle{ 
		corner_position[0],
		corner_position[1],
		source_rectangle_.w, 
		source_rectangle_.h };

	graphics.render_image(file_path_, &source_rectangle_, &destination_rectangle, angle_deg_);
}

Eigen::Vector3d Sprite::get_position() const { return center_position_; }
Eigen::Vector3d Sprite::get_velocity() const { return velocity_; }
void Sprite::delta_velocity(const Eigen::Vector3d &delta_v) { velocity_ += delta_v; }

double Sprite::get_angle_deg() const { return angle_deg_; }
double Sprite::get_omega() const { return angular_velocity_rad_; }
Eigen::Vector3d Sprite::get_omega_vector() const{return Eigen::Vector3d{ 0, 0, angular_velocity_rad_ };}
void Sprite::delta_omega(double delta_w) { angular_velocity_rad_ += delta_w; }

double Sprite::get_mass() const { return mass_; }


Eigen::Vector2i Sprite::get_corner_position() const
{
	Eigen::Vector2i corner_position{};
	corner_position[0] = static_cast<int>(center_position_[0] - source_rectangle_.w / 2);
	corner_position[1] = static_cast<int>(center_position_[1] - source_rectangle_.h / 2);
	return corner_position;
}



}// namespace pong