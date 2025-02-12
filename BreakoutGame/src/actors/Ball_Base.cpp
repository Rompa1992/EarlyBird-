#include "actors/Ball_Base.h"

namespace bo
{
	Ball_Base::Ball_Base(eb::World* owningWorld, float circleRadius, sf::Color color)
		: Actor{ owningWorld, circleRadius, color },
		_velocity{ 10.f, 10.f }
	{
	}
	void Ball_Base::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
	}

	void Ball_Base::BeginPlay()
	{
		Actor::BeginPlay();
	}
}