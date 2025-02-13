#pragma once

#include "actors/Ball_Base.h"
#include "SFML/Graphics.hpp"

using namespace eb;

namespace bo
{
	class Ball_Regular : public Ball_Base
	{
	public:
		Ball_Regular(World* owningWorld, float circleRadius, sf::Color color);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;
		virtual void OnActorBeginOverlap(Actor* hitActor) override;
		virtual void OnActorEndOverlap(Actor* hitActor) override;

	private:
		sf::Vector2f GetBallHitNormal(const sf::Vector2f ballVelocity, const sf::FloatRect& blockBounds, const sf::FloatRect& ballBounds);


	};
}