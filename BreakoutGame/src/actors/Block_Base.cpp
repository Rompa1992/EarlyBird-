#include "actors/Block_Base.h"

namespace bo
{
	Block_Base::Block_Base(eb::World* owningWorld, sf::Vector2f rectSize, sf::Color color)
		: eb::Actor{ owningWorld, rectSize, color }
	{
	}

	void Block_Base::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
	}

	void Block_Base::BeginPlay()
	{
		Actor::BeginPlay();
	}
}
