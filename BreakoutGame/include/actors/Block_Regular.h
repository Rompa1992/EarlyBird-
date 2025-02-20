#pragma once

#include "actors/Block_Base.h"

namespace bo
{
	class Block_Regular : public Block_Base
	{
	public:
		Block_Regular(eb::World* owningWorld, sf::Color color, sf::Vector2f rectSize = DefaultRectSize);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;
		virtual void OnActorBeginOverlap(Actor* hitActor) override;
		virtual void OnActorEndOverlap(Actor* hitActor) override;

	private: /// TODO: move should destroy to base and handle destry better. 
		bool _shouldDestroyNextFrame;

	};
}