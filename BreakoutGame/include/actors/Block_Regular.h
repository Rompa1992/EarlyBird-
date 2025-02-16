#pragma once

#include "actors/Block_Base.h"

namespace bo
{
	class Block_Regular : public Block_Base
	{
	public:
		Block_Regular(eb::World* owningWorld, sf::Vector2f rectSize, sf::Color color);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;
		virtual void OnActorBeginOverlap(Actor* hitActor) override;
		virtual void OnActorEndOverlap(Actor* hitActor) override;

		void SpawnBlocks(eb::World* currentWorld);

	};
}