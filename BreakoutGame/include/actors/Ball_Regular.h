#pragma once

#include "actors/Ball_Base.h"

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
		bool _hasHitActor;

	};
}