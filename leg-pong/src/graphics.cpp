#include "graphics.h"

#include <iostream>

namespace pong {

Graphics::Graphics()
{
	auto SDL_init_failure = SDL_Init(SDL_INIT_EVERYTHING);
	if (SDL_init_failure) {
		std::cerr << "Error, SDL failed to initialize" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	bool TTF_init_failure = TTF_Init();
	if (TTF_init_failure) {
		std::cerr << "Error, TTF failed to initialize" << std::endl;;
		exit(EXIT_FAILURE);
	}

	window_ = SDL_CreateWindow("Leg Pong", 50, 50, 800, 600, 0);
	renderer_ = SDL_CreateRenderer(window_, 0, 0);
}



Graphics::~Graphics()
{
	SDL_Quit();
}



void Graphics::flip() 
{
	SDL_RenderPresent(renderer_);
}

bool Graphics::load_image(const std::string& path_name)
{
	//Check if image already loaded
	if (textures_.count(path_name) == 0) {

		//load image into textures map
		auto surface = IMG_Load(path_name.c_str());
		textures_[path_name] = SDL_CreateTextureFromSurface(renderer_, surface);

		if (textures_[path_name] == NULL) {
			std::cerr << "Error creating texture: " << path_name << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

void Graphics::set_background(const std::string& path_name)
{
	load_image(path_name);
	background_path = path_name;
}



void Graphics::render_image(const std::string& path_name, const SDL_Rect* const source_rectangle, const SDL_Rect * const destination_rectangle,
	double degreesRotated, bool mirrorH, bool mirrorV)  
{

	//mirroring
	SDL_RendererFlip mirror = SDL_FLIP_NONE;
	if (mirrorH && mirrorV) mirror = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	else if (mirrorH) mirror = SDL_FLIP_HORIZONTAL;
	else if (mirrorV) mirror = SDL_FLIP_VERTICAL;

	int render_success = SDL_RenderCopyEx(renderer_, textures_[path_name], source_rectangle, destination_rectangle, degreesRotated, NULL, mirror);

	if (render_success == -1) {
		std::cerr << "Error rendering: " << path_name << std::endl;
		exit(EXIT_FAILURE);
	}
}



void Graphics::clear()
{
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 1);
	SDL_RenderClear(renderer_);

}


} // namespace pong