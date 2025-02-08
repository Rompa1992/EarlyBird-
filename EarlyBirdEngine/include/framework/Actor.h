#pragma once 

#include "framework/Object.h"
#include "SFML/Graphics.hpp"
#include "utilities/Core.h"

class b2Body;

namespace eb
{
	class World;
	class Actor : public Object
	{
	public:
		Actor(World* owningWorld);

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);
		void AddActorLocationOffset(const sf::Vector2f& offsetAmount);

		virtual void Destroy() override;

		virtual void OnBeginPlay();
		virtual void Tick();
		virtual void OnActorBeginOverlap(Actor* hitActor);
		virtual void OnActorEndOverlap(Actor* hitActor);

		// From here take some quick notes of the lightYears code, write down what is needed for this game and make it without reference. 

	private:


	};

}