#pragma once 

#include "framework/Actor.h"

using namespace eb;

namespace bo
{
	class Ball_Base : public Actor
	{
	public:
		Ball_Base(eb::World* owningWorld, float circleRadius = 50.f, sf::Color color = sf::Color::Magenta);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

	protected:
		sf::Vector2f _velocity;
	};
}