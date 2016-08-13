#pragma once

#include <SDL.h>
#include <Eigen\dense>
#include <cmath>
#include <string>


namespace pong {

class Graphics;
class Input;

class Sprite
{
public:
	Sprite();
	Sprite(Graphics& graphics, const std::string& file_path, SDL_Rect source_rect, const Eigen::Vector2d &position);
	~Sprite();
	
	virtual void update(Uint32 elapsed_time);
	void draw(Graphics& graphics);

protected:

	std::string file_path_;
	SDL_Rect source_rectangle_;

	Eigen::Vector2d position_;
	double angle_rad_=0;

private:

};


} // namespace pong