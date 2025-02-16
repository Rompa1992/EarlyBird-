#pragma once

#include "actors/Block_Base.h"
 
namespace bo
{
	class eb::World;
	class Block_Boundry : public Block_Base
	{
	public:
		Block_Boundry(eb::World* owningWorld, sf::Vector2f rectSize, sf::Color color = sf::Color::Transparent);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

		void SpawnBoundry(eb::World* currentWorld);
	};
}