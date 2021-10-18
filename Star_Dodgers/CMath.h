#ifndef __CMATH_H__
#define __CMATH_H__

#define _USE_MATH_DEFINES
#include <math.h>

#include <SFML/Graphics.hpp>

namespace cmath {
	extern sf::Clock* g_clock;

	static float Mag(sf::Vector2f _a) {
		return abs(sqrt(_a.x * _a.x + _a.y * _a.y));
	}

	static float Distance(sf::Vector2f _a, sf::Vector2f _b)
	{
		return Mag(_a - _b);
	}

	static sf::Vector2f Normalize(sf::Vector2f _a) {
		return _a / Mag(_a);
	}

	static sf::Vector2f Abs(sf::Vector2f _a) {
		return sf::Vector2f(std::abs(_a.x), std::abs(_a.y));
	}

	static float Degrees(float _rad) {
		return _rad * (180.0f / (float)M_PI);
	}

	static float Radians(float _deg) {
		return _deg / (180.0f / (float)M_PI);
	}

	template <typename T>
	static T Clamp(const T& n, const T& lower, const T& upper) {
		return std::max(lower, std::min(n, upper));
	}

	static sf::Vector2f Rotate(sf::Vector2f _a, float _degrees) {

		float theta = Radians(_degrees);

		float cs = cos(theta);
		float sn = sin(theta);

		float px = _a.x * cs - _a.y * sn;
		float py = _a.x * sn + _a.y * cs;

		return { px, py };
	}

	
}
#endif // __CMATH_H__