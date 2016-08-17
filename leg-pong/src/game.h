#pragma once

#include "graphics.h"
#include "input.h"
#include "audio.h"
#include "leg.h"
#include "ball.h"


namespace pong {



enum GameState {
	GAME_RESET,
	GAME_PAUSED,
	GAME_RUNNING
};



class Game
{
public:
	Game();
	~Game();

private:
	Graphics graphics_;
	Input input_;
	Audio audio_;

	Player player_;
	Opponent opponent_;
	Ball ball_;

	int score_{ 0 };
	GameState game_state_ = GAME_RESET;
	
	Uint32 last_update_time_;
	const unsigned k_minimum_frame_time_{ 5u };
	const unsigned k_maximum_frame_time_{ 50u };

	void initialize();
	void loop();

	unsigned delay_timer();
	void update(Uint32 elapsed_time);
	void draw();

	void reset();

};

} // namespace pong
