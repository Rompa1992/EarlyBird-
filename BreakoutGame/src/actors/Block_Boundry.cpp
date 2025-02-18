#include "actors/Block_Boundry.h"

#include "utilities/Core.h"
#include "framework/World.h"

namespace bo
{
	Block_Boundry::Block_Boundry(eb::World* owningWorld, sf::Color color, sf::Vector2f rectSize)
		: Block_Base{ owningWorld, color, rectSize }
	{
	}

	void Block_Boundry::Tick(float deltaTime)
	{
	}

	void Block_Boundry::BeginPlay()
	{
		Block_Base::BeginPlay();
		SetPhysicsEnabled(true);
	}

}