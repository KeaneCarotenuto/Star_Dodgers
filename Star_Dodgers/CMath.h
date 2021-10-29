//==========================================================
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//----------------------------------------------------------
// (c) 2021 Media Design School
//==========================================================
//   File Name  : CMath.h
//----------------------------------------------------------
//  Description : Contains various useful maths functions
//----------------------------------------------------------
//    Author    : Keane Carotenuto
//----------------------------------------------------------
//    E-mail    : KeaneCarotenuto@gmai.com
//==========================================================

#ifndef __CMATH_H__
#define __CMATH_H__

#define _USE_MATH_DEFINES
#include <math.h>

#include <SFML/Graphics.hpp>

namespace cmath {
	extern sf::Clock* g_clock;

	/// <summary>
	/// Get magnitude of vector
	/// </summary>
	/// <param name="_a"></param>
	/// <returns></returns>
	static float Mag(sf::Vector2f _a) {
		return abs(sqrt(_a.x * _a.x + _a.y * _a.y));
	}

	/// <summary>
	/// Get Distance between two points
	/// </summary>
	/// <param name="_a"></param>
	/// <param name="_b"></param>
	/// <returns></returns>
	static float Distance(sf::Vector2f _a, sf::Vector2f _b)
	{
		return Mag(_a - _b);
	}

	/// <summary>
	/// Normalize vector
	/// </summary>
	/// <param name="_a"></param>
	/// <returns></returns>
	static sf::Vector2f Normalize(sf::Vector2f _a) {
		return _a / Mag(_a);
	}

	/// <summary>
	/// Absolute a vector
	/// </summary>
	/// <param name="_a"></param>
	/// <returns></returns>
	static sf::Vector2f Abs(sf::Vector2f _a) {
		return sf::Vector2f(std::abs(_a.x), std::abs(_a.y));
	}

	/// <summary>
	/// Convert rad to deg
	/// </summary>
	/// <param name="_rad"></param>
	/// <returns></returns>
	static float Degrees(float _rad) {
		return _rad * (180.0f / (float)M_PI);
	}

	/// <summary>
	/// Convert deg to rad
	/// </summary>
	/// <param name="_deg"></param>
	/// <returns></returns>
	static float Radians(float _deg) {
		return _deg / (180.0f / (float)M_PI);
	}

	/// <summary>
	/// Clamps value between two other values
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="n"></param>
	/// <param name="lower"></param>
	/// <param name="upper"></param>
	/// <returns></returns>
	template <typename T>
	static T Clamp(const T& n, const T& lower, const T& upper) {
		return std::max(lower, std::min(n, upper));
	}

	/// <summary>
	/// Rotates a vector by some amount
	/// </summary>
	/// <param name="_a"></param>
	/// <param name="_degrees"></param>
	/// <returns></returns>
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