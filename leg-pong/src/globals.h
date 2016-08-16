#pragma once

#include <cmath>
#include <iostream>

namespace pong {

constexpr unsigned int screen_height() { return 600; }
constexpr unsigned int screen_width() { return 800; }

inline double to_radians(double degrees) { return degrees*M_PI / 180.0; }
inline double to_degrees(double radians) { return radians*180.0 / M_PI; }

inline double quadratic_neg(double a, double b, double c) 
{
	if (b*b - 4 * a*c < 0)
	{
		std::cerr << "Negative determinant" << std::endl;
		exit(EXIT_FAILURE);
	}

	return (-b - pow(b*b - 4 * a*c, 0.5)) / (2 * a);
}

} // namespace pong