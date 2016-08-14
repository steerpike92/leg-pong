#include "input.h"

namespace pong {

void Input::process_events()  {
	
	pressed_keys_.fill(false);
	released_keys_.fill(false);

	pressed_buttons_.fill(false);
	pressed_buttons_.fill(false);

	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_MOUSEMOTION:
			process_mouse_movement_event(event);
			continue;
		case SDL_MOUSEBUTTONDOWN:
			process_button_down_event(event);
			continue;
		case SDL_MOUSEBUTTONUP:
			process_button_up_event(event);
			continue;
		case(SDL_QUIT):
			quit_flag_ = true;
			return;
		case(SDL_KEYDOWN):
			if (event.key.repeat == 0)
				process_key_down_event(event);
			continue;
		case(SDL_KEYUP):
			process_key_up_event(event);
			continue;
		}

	}
}

bool Input::is_key_pressed(SDL_Scancode scancode) const
{
	return pressed_keys_[scancode];
}

bool Input::is_key_held(SDL_Scancode scancode) const
{
	return held_keys_[scancode];
}

bool Input::is_key_released(SDL_Scancode scancode) const
{
	return released_keys_[scancode];
}

bool Input::is_button_pressed(int button_index) const
{
	return pressed_buttons_[button_index];
}

bool Input::is_button_held(int button_index) const
{
	return held_buttons_[button_index];
}

bool Input::is_button_released(int button_index) const
{
	return released_buttons_[button_index];
}



SDL_Point Input::get_mouse_point() const {
	return mouse_point_;
}



void Input::process_key_down_event(const SDL_Event &event)  {
	pressed_keys_[event.key.keysym.scancode] = true;
	held_keys_[event.key.keysym.scancode] = true;
}



void Input::process_key_up_event(const SDL_Event &event)  {
	held_keys_[event.key.keysym.scancode] = false;
	released_keys_[event.key.keysym.scancode] = true;
}



void Input::process_mouse_center_position(const SDL_Event &event) 
{
	mouse_point_.x = event.button.x;
	mouse_point_.y = event.button.y;
}



//Called when button pressed
void Input::process_button_down_event(const SDL_Event& event)  {

	pressed_buttons_[event.button.button] = true;

	held_buttons_[event.button.button] = true;

	//store center_position data
	process_mouse_center_position(event);

}



void Input::process_button_up_event(const SDL_Event& event)  {
	released_buttons_[event.button.button] = true;
	held_buttons_[event.button.button] = false;

	process_mouse_center_position(event);
}



void Input::process_mouse_movement_event(const SDL_Event& event)  {
	process_mouse_center_position(event);
}







} // namespace pong