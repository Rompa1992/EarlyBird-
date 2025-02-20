#pragma once

#include "actors/Ball_Base.h"
#include "SFML/Graphics.hpp"


namespace bo
{
	class Core;
	class Ball_Regular : public Ball_Base
	{
	public:
		Ball_Regular(eb::World* owningWorld, sf::Color color = sf::Color::Cyan, float radiusSize = DefaultBallSize);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;
		virtual void OnActorBeginOverlap(Actor* hitActor) override;
		virtual void OnActorEndOverlap(Actor* hitActor) override;

	};
}