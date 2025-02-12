#pragma once 

#include "framework/Object.h"
#include "SFML/Graphics.hpp"
#include "utilities/Core.h"


class b2Body;																																	// outside of namespace eb::

namespace eb
{
	class World;
	class Actor : public Object
	{
	public:
		// Rectangle
		Actor(World* owningWorld, sf::Vector2f rectSize = {50.f, 50.f}, sf::Color color = {sf::Color::Cyan});

		// Circle
		Actor(World* owningWorld, float radiusSize = 50.f, sf::Color color = { sf::Color::Cyan });

		void BeginPlayInternal();																												// Called From World::TickInternal();
		void TickInternal(float deltaTime);																										// Called From World::TickInternal();
		void Render(sf::RenderWindow& window);																									// Called From World::Render();
		void AddActorLocationOffset(const sf::Vector2f& offsetAmount);

		//TODO: Document physics process & its cpp - figure out the scale thing. make sure the physics boxes are alliged with the actors correctly. AssetManager start.

		virtual void Destroy() override;

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void OnActorBeginOverlap(Actor* hitActor);
		virtual void OnActorEndOverlap(Actor* hitActor);

		void SetActorLocation(const sf::Vector2f& newLocation);
		void SetActorRotation(const float newRotation);
		void SetPhysicsEnabled(bool enable);

		// getters
		sf::FloatRect GetActorGlobalRectBounds() const;

		sf::Vector2u GetWindowSize() const;

		const World* GetWorld() const { return _owningWorld; }
		World* GetWorld() { return _owningWorld; }

		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;
		shared_ptr<sf::Shape> GetBaseShape() const { return _baseShapeActor; }
		// end getters

		virtual ~Actor();

	private:
		// Physics
		void InitPhysics();
		void UnInitPhysics();
		void UpddatePhysicsTransform();
		void RenderDebugPhysics(sf::RenderWindow& window);

		shared_ptr<sf::Shape> _baseShapeActor;

		World* _owningWorld;
		bool _hasBeganPlay;

		b2Body* _physicsBody;
		bool _isPhysicsEnabled;
		bool _debugDrawEnabled = true;

	};
}

