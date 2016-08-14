#pragma once

#include <SDL.h>

#include <array>

namespace pong {

class Input
{
public:
	//Call at beggining of every frame, handles all events, updates key arrays
	void process_events() ;

	//report key states
	bool is_key_pressed(SDL_Scancode scancode) const;
	bool is_key_held(SDL_Scancode scancode) const;
	bool is_key_released(SDL_Scancode scancode) const;

	//report mouse states
	bool is_button_pressed(int button_index) const;
	bool is_button_held(int button_index) const;
	bool is_button_released(int button_index) const;

	//Report mouse location
	SDL_Point get_mouse_point() const;

	//quit flag
	bool quit_flag_ = false;
private:

	//updates key maps
	void process_key_up_event(const SDL_Event &event);
	void process_key_down_event(const SDL_Event &event);

	void process_button_down_event(const SDL_Event& event);
	void process_button_up_event(const SDL_Event& event);
	void process_mouse_movement_event(const SDL_Event& event);
	void process_mouse_center_position(const SDL_Event& event);

	//array of key states
	std::array<bool, SDL_NUM_SCANCODES> pressed_keys_{};
	std::array<bool, SDL_NUM_SCANCODES> held_keys_{};
	std::array<bool, SDL_NUM_SCANCODES> released_keys_{};

	//MOUSE BUTTON DATA
	std::array<bool, 4> pressed_buttons_{};
	std::array<bool, 4> held_buttons_{};
	std::array<bool, 4> released_buttons_{};

	//MOUSE LOCATION DATA
	SDL_Point mouse_point_;
};



} // namespace pong
