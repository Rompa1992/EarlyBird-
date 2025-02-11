#include "utilities/Math.h"

#include <random>

namespace eb
{
	constexpr float PI = 3.1415926535f;

	float DegreesToRadians(const float degrees)
	{
		return degrees * (PI / 180.f);
	}

	float RadiansToDegrees(const float radians)
	{
		return radians * (180.f / PI);
	}

	sf::Vector2f RotationToVector(const float rotation)
	{
		float radians = DegreesToRadians(rotation);
		return sf::Vector2f(std::cos(radians), std::sin(radians));
	}

	float RandomRange(float min, float max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_real_distribution<float> distribution{ min, max };

		return distribution(gen);
	}
}