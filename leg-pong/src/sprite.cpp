#include "sprite.h"

#include "graphics.h"
#include "input.h"

namespace pong {



Sprite::Sprite(){}
Sprite::~Sprite(){}



Sprite::Sprite(Graphics& graphics, const std::string& file_path, SDL_Rect source_rectangle, const Eigen::Vector2d &center_position, double mass) :
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
	angle_deg_ += angular_velocity_ * elapsed_time / 1000.0;
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



Eigen::Vector2i Sprite::get_corner_position() const
{
	Eigen::Vector2i corner_position{};
	corner_position[0] = static_cast<int>(center_position_[0] - source_rectangle_.w / 2);
	corner_position[1] = static_cast<int>(center_position_[1] - source_rectangle_.h / 2);
	return corner_position;
}



}// namespace pong