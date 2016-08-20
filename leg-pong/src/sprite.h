#pragma once

#include <SDL.h>
#include <Eigen\dense>
#include <cmath>
#include <string>


namespace pong {

class Game;
class Graphics;
class Input;

class Sprite
{
	friend void test(Game* game);
public:
	Sprite();
	Sprite(Graphics& graphics, const std::string& file_path, SDL_Rect source_rect, const Eigen::Vector3d &center_position, double angle_rad, double mass);
	~Sprite();
	
	virtual void update(Uint32 elapsed_time);
	void draw(Graphics& graphics) const;

	Eigen::Vector3d get_position() const;
	Eigen::Vector3d get_velocity() const;
	void delta_velocity(const Eigen::Vector3d &delta_v);

	double get_angle_deg() const;
	double get_omega() const;
	Eigen::Vector3d get_omega_vector() const;
	void delta_omega(double delta_w);

	double get_mass() const;

protected:
	Eigen::Vector3d center_position_, previous_center_position_;
	Eigen::Vector3d velocity_{ 0,0,0 };

	double angle_rad_{ 0 }, previous_angle_rad_{ 0 };
	double angular_velocity_rad_{ 0 };
	double mass_{ 0 };
private:
	std::string file_path_;
	SDL_Rect source_rectangle_;

	Eigen::Vector2i get_corner_position() const;

};


} // namespace pong