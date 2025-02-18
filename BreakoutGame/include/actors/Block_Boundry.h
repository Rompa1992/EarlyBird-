#pragma once

#include "actors/Block_Base.h"
 
namespace bo
{
	class eb::World;
	class Block_Boundry : public Block_Base
	{
	public:
		Block_Boundry(eb::World* owningWorld, sf::Color color, sf::Vector2f rectSize);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

	};
}