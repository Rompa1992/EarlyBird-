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
		Actor(eb::World* owningWorld, sf::Color color, sf::Vector2f rectSize);

		// Circle 
		/// Refactor this the same as the blocks, decide whether or not the static cinsts should be constexpr and have getters etc. 
		Actor(World* owningWorld, sf::Color color, float radiusSize);

		void BeginPlayInternal();																												// Called From World::TickInternal();
		void TickInternal(float deltaTime);																										// Called From World::TickInternal();
		void Render(sf::RenderWindow& window);																									// Called From World::Render();
		void AddActorLocationOffset(const sf::Vector2f& offsetAmount);

		virtual void Destroy() override;

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void OnActorBeginOverlap(Actor* hitActor);
		virtual void OnActorEndOverlap(Actor* hitActor);

		// setters
		void SetActorLocation(const sf::Vector2f& newLocation);
		void SetActorRotation(const float newRotation);
		void SetPhysicsEnabled(bool enable);

		// getters
		sf::FloatRect GetActorGlobalRectBounds() const;

		sf::Vector2u GetWindowSize() const;

		const World* GetWorld() const { return _owningWorld; }
		World* GetWorld() { return _owningWorld; }

		bool IsRectShape() const { return _isRectShape; }
		bool IsCircleShape() const { return _isCircleShape; }

		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;

		// end getters

		virtual ~Actor();

	private:
		// Physics
		void InitPhysics();
		void UnInitPhysics();
		void UpddatePhysicsTransform();
		void RenderDebugPhysics(sf::RenderWindow& window);

		shared_ptr<sf::Shape> _baseShapeActor;
		bool _isRectShape;
		bool _isCircleShape;

		World* _owningWorld;
		bool _hasBeganPlay;

		b2Body* _physicsBody;
		bool _isPhysicsEnabled;
		bool _debugDrawEnabled = true;

	};
}

