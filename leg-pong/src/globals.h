#pragma once

#include <cmath>

namespace pong {

constexpr unsigned int screen_height() { return 600; }
constexpr unsigned int screen_width() { return 800; }

inline double to_radians(double degrees) { return degrees*M_PI / 180.0; }
inline double to_degrees(double radians) { return radians*180.0 / M_PI; }

} // namespace pong