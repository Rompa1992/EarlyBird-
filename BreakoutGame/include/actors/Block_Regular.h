#pragma once

#include "actors/Block_Base.h"

using namespace eb;

namespace bo
{
	class Block_Regular : public Block_Base
	{
	public:
		Block_Regular(World* owningWorld, sf::Vector2f rectSize, sf::Color color);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

		void SpawnBlocks(World* currentWorld);

	};
}