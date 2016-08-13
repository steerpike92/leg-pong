#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <unordered_map>
#include <string>

namespace pong {

class Graphics
{
public:
	Graphics();
	~Graphics();

	
	void flip();

	void load_image(const std::string& path_name);
	void set_background(const std::string& path_name);

	void render_image(const std::string &pathName, const SDL_Rect* const source_rectangle, const SDL_Rect * const destination_rectangle,
		double degreesRotated=0.0, bool mirrorH=false, bool mirrorV=false);
private:
	SDL_Window *window_;
	SDL_Renderer *renderer_;
	TTF_Font *font_;

	std::unordered_map <std::string, SDL_Texture*> textures_;
	std::string background_path_;

	void clear();



};



} // namespace pong
