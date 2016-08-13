#include "sprite.h"

#include "graphics.h"
#include "input.h"

namespace pong {


Sprite::Sprite()
{
}



Sprite::Sprite(Graphics& graphics, const std::string& file_path, SDL_Rect source_rectangle, SDL_Point position) :
	file_path_(file_path),
	source_rectangle_(source_rectangle),
	position_(position)
{
	graphics.load_image(file_path_);
}



Sprite::~Sprite()
{
}



void Sprite::update(Input &input, Uint32 elapsed_time)
{
	if (input.is_key_held(SDL_SCANCODE_LEFT))
		position_.x -= elapsed_time / 4;
	if (input.is_key_held(SDL_SCANCODE_RIGHT))
		position_.x += elapsed_time / 4;
}



void Sprite::draw(Graphics & graphics)
{
	SDL_Rect destination_rectangle{ position_.x, position_.y, source_rectangle_.w, source_rectangle_.h };
	graphics.render_image(file_path_, &source_rectangle_, &destination_rectangle);
}



}// namespace pong