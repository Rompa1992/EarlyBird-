#include "actors/Block_Base.h"

namespace bo
{
	const sf::Vector2f Block_Base::DefaultRectSize = { 100.f, 25.f };

	Block_Base::Block_Base(eb::World* owningWorld, sf::Color color, sf::Vector2f rectSize)
		: eb::Actor{ owningWorld, color, rectSize }
	{
		rectSize = { 400.f, 600.f };
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
