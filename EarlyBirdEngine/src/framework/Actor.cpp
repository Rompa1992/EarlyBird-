#include "framework/Actor.h"

namespace eb
{
	// public:
	// =======
	Actor::Actor(World* owningWorld)
	{
	}

	// void
	void Actor::BeginPlayInternal()
	{
	}

	void Actor::TickInternal(float deltaTime)
	{
	}

	void Actor::Render(sf::RenderWindow& window)
	{
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmount)
	{
	}

	// virtual void override
	void Actor::Destroy()
	{
	}


	// virtual void 
	void Actor::OnBeginPlay()
	{
	}

	void Actor::Tick()
	{
	}

	void Actor::OnActorBeginOverlap(Actor* hitActor)
	{
	}

	void Actor::OnActorEndOverlap(Actor* hitActor)
	{
	}

}

