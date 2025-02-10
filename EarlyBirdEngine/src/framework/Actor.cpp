#include "framework/Actor.h"

#include "utilities/Core.h"
#include "framework/World.h"

// TODO: link physics API
// #include <box2d/b2_body.h>

namespace eb
{
	// public:
	// =======
	Actor::Actor(World* owningWorld, sf::Vector2f rectSize, sf::Color color)
		: _owningWorld{ owningWorld },
		_baseShapeActor{ std::make_shared<sf::RectangleShape>(rectSize) },
		_hasBeganPlay{ false },
		_isPhysicsEnabled{ false }
	{
		_baseShapeActor->setFillColor(color);
	}

	Actor::Actor(World* owningWorld, float radiusSize, sf::Color color)
		: _owningWorld{ owningWorld },
		_baseShapeActor{ std::make_shared<sf::CircleShape>(radiusSize) },
		_hasBeganPlay{ false },
		_isPhysicsEnabled{ false }
	{
		_baseShapeActor->setFillColor(color);
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
			if (_baseShapeActor)
				window.draw(*_baseShapeActor);
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
		//sf::Vector2f newLocation = GetActorLocation() + sf::Vector2f(1.f, 0.f);
		//SetActorLocation(newLocation);
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

		_baseShapeActor->setPosition(newLocation);

		// If physics is enabled, update physics transform
		if (_isPhysicsEnabled)
		{
			UpddatePhysicsTransform();
		}
	}



	// getters
	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return sf::FloatRect();
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return _owningWorld->GetWindowSize();
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return _baseShapeActor->getPosition();
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