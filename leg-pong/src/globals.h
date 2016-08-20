#pragma once

#include <cmath>
#include <iostream>

namespace pong {

constexpr unsigned int screen_height() { return 600; }
constexpr unsigned int screen_width() { return 800; }

inline double to_radians(double degrees) { return degrees*M_PI / 180.0; }
inline double to_degrees(double radians) { return radians*180.0 / M_PI; }



namespace math {


//returns false if imaginary solution, true otherwise.
//a, b, c, from quadratic formula.
//first_root specifies which root will be found. true-> left root, false-> right root.
//root is stuffed with the solution, if it exists.
inline bool quadratic(double a, double b, double c, bool first_root, double& root)
{
	//check for negative determinant
	if (b*b - 4 * a*c < 0)
	{
		root = 0;
		return false;
	}

	double sign = (first_root) ? -1 : 1;

	root = (-b + sign*pow(b*b - 4 * a*c, 0.5)) / (2 * a);
	return true;
}


struct Vertex
{
	double x, t;
};


struct Point
{
	double x, y, t;
};


inline Vertex find_vertex(double Acceleration, double Vo, double Xo, double To)
{
	Vertex vertex;
	vertex.t = -Vo / Acceleration;
	vertex.x = Xo + Vo*vertex.t + .5*Acceleration* pow(vertex.t, 2);
	vertex.t += To;

	return vertex;
}

} // namespace math
} // namespace pong