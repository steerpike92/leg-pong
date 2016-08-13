#pragma once

#include "graphics.h"
#include "input.h"
#include "sprite.h"

namespace pong {

class Game
{
public:
	Game();
	~Game();

private:
	Graphics graphics_;
	Input input_;
	Sprite player_;

	void initialize();
	void loop();

	void update(Uint32 elapsed_time);
	void draw();


};

} // namespace pong
