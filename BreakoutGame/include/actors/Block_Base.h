#pragma once 

#include "framework/Actor.h"

using namespace eb;

namespace bo
{
	class Block_Base : public Actor
	{
	public:
		Block_Base(eb::World* owningWorld, sf::Vector2f rectSize = { 50.f, 50.f }, sf::Color color = sf::Color::Cyan);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

	private:
		float _velocity;
	};
}