#include "actors/Block_Regular.h"

#include "framework/World.h"
#include "levels/Level_Base.h"


namespace bo
{
	// public:
	// =======
	Block_Regular::Block_Regular(eb::World* owningWorld, sf::Color color, sf::Vector2f rectSize)
		: Block_Base{ owningWorld, color, rectSize },
		_shouldDestroyNextFrame{ false }
	{
	}

	void Block_Regular::Tick(float deltaTime)
	{
		/// TODO: fix this delete
		if (_shouldDestroyNextFrame)
		{
			Destroy(); /// need to store blocks somewhere
			_shouldDestroyNextFrame = false;
		}

	}

	void Block_Regular::BeginPlay()
	{
		Block_Base::BeginPlay();
		SetPhysicsEnabled(true);
		
	}

	void Block_Regular::OnActorBeginOverlap(Actor* hitActor)
	{
		
		GetCurrentLevel()->SubtractLevelBlocks();
		_shouldDestroyNextFrame = true;
	}

	void Block_Regular::OnActorEndOverlap(Actor* hitActor)
	{
	}
}
