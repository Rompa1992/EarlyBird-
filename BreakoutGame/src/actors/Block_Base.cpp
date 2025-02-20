#include "actors/Block_Base.h"

#include "levels/Level_Base.h"

namespace bo
{
	const sf::Vector2f Block_Base::DefaultRectSize = { 100.f, 25.f };

	Block_Base::Block_Base(eb::World* owningWorld, sf::Color color, sf::Vector2f rectSize)
		: eb::Actor{ owningWorld, color, rectSize }
	{
		_currentLevel = dynamic_cast<Level_Base*>(owningWorld);
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
