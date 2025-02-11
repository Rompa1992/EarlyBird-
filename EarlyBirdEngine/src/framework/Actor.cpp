#include "framework/Actor.h"

#include <box2d/b2_body.h>

#include "framework/PhysicsSystem.h"
#include "framework/World.h"
#include "utilities/Core.h"
#include "utilities/Math.h"

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
		_physicsBody{ nullptr },
		_isPhysicsEnabled{ false }
	{
		_baseShapeActor->setFillColor(color);
	}

	Actor::Actor(World* owningWorld, float radiusSize, sf::Color color)
		: _owningWorld{ owningWorld },
		_baseShapeActor{ std::make_shared<sf::CircleShape>(radiusSize) },
		_hasBeganPlay{ false },
		_physicsBody{ nullptr },
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

			if (_debugDrawEnabled && _physicsBody) 
				RenderDebugPhysics(window);
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
		SetPhysicsEnabled(true);
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
		UpddatePhysicsTransform();
	}

	void Actor::SetPhysicsEnabled(bool enable)
	{
		_isPhysicsEnabled = enable;

		if (_isPhysicsEnabled)
			InitPhysics();
		else
			UnInitPhysics();
	}



	// getters
	sf::FloatRect Actor::GetActorGlobalRectBounds() const																			// Access through .width & .height for .x & .y
	{
		return _baseShapeActor->getGlobalBounds();
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return _owningWorld->GetWindowSize();
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return _baseShapeActor->getPosition();
	}

	float Actor::GetActorRotation() const
	{
		return _baseShapeActor->getRotation();
	}


	Actor::~Actor()
	{
	}

	// private:
	// ========

	// void
	void Actor::InitPhysics()
	{
		if (!_physicsBody)
			_physicsBody = PhysicsSystem::Get().AddListener(this);
	}

	void Actor::UnInitPhysics()
	{
		if (_physicsBody)
		{
			PhysicsSystem::Get().RemoveListener(_physicsBody);
			_physicsBody = nullptr;
		}
	}

	void Actor::UpddatePhysicsTransform()
	{
		if (_physicsBody)
		{
			float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			b2Vec2 pos{ GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale };
			
			_physicsBody->SetTransform(pos, 0.f);
		}
	}

	void Actor::RenderDebugPhysics(sf::RenderWindow& window)
	{
		if (!_physicsBody)
			return;

		sf::RectangleShape debugShape;

		if (auto rect = dynamic_cast<sf::RectangleShape*>(_baseShapeActor.get())) {
			debugShape.setSize(rect->getSize());
			debugShape.setOrigin(rect->getSize().x / 2.f, rect->getSize().y / 2.f);
		}

		float physicsScale = PhysicsSystem::Get().GetPhysicsScale();

		debugShape.setPosition(
			GetActorLocation().x * physicsScale + GetActorGlobalRectBounds().width / 2.f,
			GetActorLocation().y * physicsScale + GetActorGlobalRectBounds().height / 2.f);
		debugShape.setRotation(GetActorRotation());
		debugShape.setFillColor(sf::Color::Transparent);
		debugShape.setOutlineColor(sf::Color::Red);
		debugShape.setOutlineThickness(1.0f);

		window.draw(debugShape);
	}
}