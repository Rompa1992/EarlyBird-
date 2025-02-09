#include "framework/Actor.h"

// TODO: link physics API
// #include <box2d/b2_body.h>

namespace eb
{
	// public:
	// =======
	Actor::Actor(World* owningWorld)
		: _owningWorld{ owningWorld },
		_hasBeganPlay{ false },
		_isPhysicsEnabled{ false }
	{
	}

	// void
	void Actor::BeginPlayInternal()
	{
		if (!_hasBeganPlay)
		{
			_hasBeganPlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy())
			Tick(deltaTime);
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (!IsPendingDestroy())
		{
			// TODO: implement a draw method or variable??
			sf::RectangleShape rectangle;
		}
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmount)
	{
		SetActorLocation(GetActorLocation() + offsetAmount);
	}

	// virtual void override
	void Actor::Destroy()
	{
		UnInitPhysics();
		Object::Destroy();
	}


	// virtual void 
	void Actor::BeginPlay()
	{
		PRINT("Actor has began play");
	}

	void Actor::Tick(float deltaTime)
	{
		PRINT("Actor is Ticking");
	}

	void Actor::OnActorBeginOverlap(Actor* hitActor)
	{
		PRINT_COLOR(BLUE, "Actor Overlapped");
	}

	void Actor::OnActorEndOverlap(Actor* hitActor)
	{
		PRINT_COLOR(YELLOW, "Actor End Overlapped");
	}

	// setters
	void Actor::SetActorLocation(const sf::Vector2f& newLocation)
	{
	}

	// getters
	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return sf::FloatRect();
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return sf::Vector2f();
	}

	Actor::~Actor()
	{
	}

	// private:
	// ========

	// void
	void Actor::InitPhysics()
	{
	}

	void Actor::UnInitPhysics()
	{
	}

	void Actor::UpddatePhysicsTransform()
	{
	}

}

