#pragma once

#include <SDL.h>

#include <string>

namespace pong {

class Graphics;

class Sprite
{
public:
	Sprite();
	Sprite(Graphics &graphics, const std::string &file_path, SDL_Rect source_rect, SDL_Point position);
	~Sprite();
	
	void update();
	void draw(Graphics &graphics);

private:

	std::string file_path_;
	SDL_Rect source_rect_;
	SDL_Point position_;

};


} // namespace pong