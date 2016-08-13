#pragma once

#include "sprite.h"

namespace pong {

class Graphics;

class Ball : public Sprite
{
public:
	Ball();
	Ball(Graphics& graphics);
	~Ball();

private:

};


} // namespace pong