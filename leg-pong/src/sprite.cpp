#include "sprite.h"

#include "graphics.h"
#include "input.h"

namespace pong {


Sprite::Sprite()
{
}



Sprite::Sprite(Graphics& graphics, const std::string& file_path, SDL_Rect source_rectangle, const Eigen::Vector2d &position) :
	file_path_(file_path),
	source_rectangle_(source_rectangle),
	position_(position),
	angle_rad_(0)
{
	graphics.load_image(file_path_);
}



Sprite::~Sprite()
{
}



void Sprite::update(Uint32 elapsed_time)
{
	
}



void Sprite::draw(Graphics & graphics)
{
	SDL_Rect destination_rectangle{ 
		static_cast<int>(position_[0]), 
		static_cast<int>(position_[1]),
		source_rectangle_.w, 
		source_rectangle_.h };

	graphics.render_image(file_path_, &source_rectangle_, &destination_rectangle, angle_rad_);
}



}// namespace pong