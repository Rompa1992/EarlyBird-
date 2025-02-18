#pragma once 

#include "framework/Actor.h"

namespace bo
{
	class Block_Base : public eb::Actor
	{
	protected:
		static const sf::Vector2f DefaultRectSize;

	public:

		Block_Base(eb::World* owningWorld, sf::Color color = sf::Color::White, sf::Vector2f rectSize = DefaultRectSize);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

	};
}