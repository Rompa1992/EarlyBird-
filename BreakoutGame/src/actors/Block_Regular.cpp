#include "actors/Block_Regular.h"

#include "framework/World.h"
#include "utilities/Core.h"

namespace bo
{
	// public:
	// =======
	Block_Regular::Block_Regular(eb::World* owningWorld, sf::Color color, sf::Vector2f rectSize)
		: Block_Base{ owningWorld, color, rectSize }
	{
	}

	void Block_Regular::Tick(float deltaTime)
	{
	}

	void Block_Regular::BeginPlay()
	{
		Block_Base::BeginPlay();
		SetPhysicsEnabled(true);
	}

	void Block_Regular::OnActorBeginOverlap(Actor* hitActor)
	{
		Destroy();
	}

	void Block_Regular::OnActorEndOverlap(Actor* hitActor)
	{
	}
}
