#pragma once
#include <SFML/Graphics.hpp>

namespace cmath {
	float Mag(sf::Vector2f _a) {
		return abs(sqrt(_a.x * _a.x + _a.y * _a.y));
	}

	float Distance(sf::Vector2f _a, sf::Vector2f _b)
	{
		return Mag(_a - _b);
	}

	sf::Vector2f Normalize(sf::Vector2f _a) {
		return _a / Mag(_a);
	}
}