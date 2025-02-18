#pragma once 

#include "actors/Player.h"
#include "framework/Actor.h"


namespace bo
{
	class eb::World;
	class Player;
	class Ball_Base : public eb::Actor
	{
	protected:
		static constexpr float PlayerImpartFrictionSpeed{ 75.f };
		static constexpr float PlayerImpartSideHitSpeed{ 400.f };
		static constexpr float DefaultBallSize{ 15.f };

	public:
		Ball_Base(eb::World* owningWorld, sf::Color color = sf::Color::White, float radiusSize = DefaultBallSize);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;
		virtual void OnActorBeginOverlap(Actor* hitActor) override;
		virtual void OnActorEndOverlap(Actor* hitActor) override;


	protected:
		sf::Vector2f GetBallHitNormal(const sf::Vector2f ballVelocity, const sf::FloatRect& blockBounds, const sf::FloatRect& ballBounds);

		sf::Vector2f _velocity;

	private:
		const float _targetFrameRate;

		bool _hitActorIsBoundry;


	};
}