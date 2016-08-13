#include "ball.h"
#include "graphics.h"

namespace pong {


Ball::Ball()
{
}

Ball::Ball(Graphics& graphics) :
	Sprite(graphics, static_cast<std::string>("data/ball.png"), { 0,0,50,50 }, { 300.0,300.0 })
{

}

Ball::~Ball()
{
}

} // namespace pong