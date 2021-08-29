#ifndef __CMATH_H__
#define __CMATH_H__

#include <SFML/Graphics.hpp>

namespace cmath {
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
}
#endif // __CMATH_H__