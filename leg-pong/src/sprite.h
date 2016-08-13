#pragma once

#include <SDL.h>

#include <string>

namespace pong {

class Graphics;
class Input;

class Sprite
{
public:
	Sprite();
	Sprite(Graphics& graphics, const std::string& file_path, SDL_Rect source_rect, SDL_Point position);
	~Sprite();
	
	void update(Input& input, Uint32 elapsed_time);
	void draw(Graphics& graphics);

private:

	std::string file_path_;
	SDL_Rect source_rectangle_;
	SDL_Point position_;
	

};


} // namespace pong