#pragma once

#include "graphics.h"
#include "input.h"
#include "leg.h"
#include "ball.h"

namespace pong {

class Game
{
public:
	Game();
	~Game();

private:
	Graphics graphics_;
	Input input_;

	Player player_;
	Opponent opponent_;
	Ball ball_;

	int score_{ 0 };


	void initialize();
	void loop();

	void update(Uint32 elapsed_time);
	void draw();


};

} // namespace pong
