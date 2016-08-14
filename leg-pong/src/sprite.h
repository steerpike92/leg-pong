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
	Sprite(Graphics& graphics, const std::string& file_path, SDL_Rect source_rect, const Eigen::Vector2d &center_position, double mass);
	~Sprite();
	
	virtual void update(Uint32 elapsed_time);
	void draw(Graphics& graphics) const;

protected:
	Eigen::Vector2d center_position_, previous_center_position_;
	Eigen::Vector2d velocity_{ 0,0 };

	double angle_deg_{ 0 }, previous_angle_deg_{ 0 };
	double angular_velocity_{ 0 };
	double mass_{ 0 };
private:
	std::string file_path_;
	SDL_Rect source_rectangle_;

	Eigen::Vector2i get_corner_position() const;

};


} // namespace pong