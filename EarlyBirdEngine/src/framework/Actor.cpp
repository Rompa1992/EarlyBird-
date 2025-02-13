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
		_isRectShape{ true },
		_isCircleShape{ false },
		_hasBeganPlay{ false },
		_physicsBody{ nullptr },
		_isPhysicsEnabled{ false }
	{
		_baseShapeActor->setFillColor(color);
	}

	Actor::Actor(World* owningWorld, float radiusSize, sf::Color color)
		: _owningWorld{ owningWorld },
		_baseShapeActor{ std::make_shared<sf::CircleShape>(radiusSize) },
		_isRectShape{ false },
		_isCircleShape{ true },
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
		//PRINT("Actor has began play");
	}

	void Actor::Tick(float deltaTime)
	{

	}

	void Actor::OnActorBeginOverlap(Actor* hitActor)
	{
		//PRINT_COLOR(BLUE, "Actor Overlapped");
	}

	void Actor::OnActorEndOverlap(Actor* hitActor)
	{
		//PRINT_COLOR(YELLOW, "Actor End Overlapped");
	}

	// setters
	void Actor::SetActorLocation(const sf::Vector2f& newLocation)
	{

		_baseShapeActor->setPosition(newLocation);
		UpddatePhysicsTransform();
	}

	void Actor::SetActorRotation(const float newRotation)
	{
		_baseShapeActor->setRotation(newRotation);
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

	// Physics ======================================================================
	void Actor::InitPhysics()
	{
		if (!_physicsBody)
		{
			_physicsBody = PhysicsSystem::Get().AddListener(this);
		}
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

			b2Vec2 pos{};

			if (_isRectShape)
				 pos = { (GetActorLocation().x + GetActorGlobalRectBounds().width / 2) * physicsScale, 
						 (GetActorLocation().y + GetActorGlobalRectBounds().height / 2) * physicsScale };
			else
				 pos = { (GetActorLocation().x + GetActorGlobalRectBounds().width / 2) * physicsScale, 
						 (GetActorLocation().y + GetActorGlobalRectBounds().width / 2) * physicsScale };

			float rotation = DegreesToRadians(GetActorRotation());

			_physicsBody->SetTransform(pos, rotation);
		}
	}

	void Actor::RenderDebugPhysics(sf::RenderWindow& window)
	{
		sf::RectangleShape debugShape;
		sf::Vector2f currentBodyBounds = { PhysicsSystem::Get().GetBodyBounds(this).x, PhysicsSystem::Get().GetBodyBounds(this).y };
		sf::Vector2f currentBodyPosition = { PhysicsSystem::Get().GetBodyPosition().x, PhysicsSystem::Get().GetBodyPosition().y };

		debugShape.setSize(currentBodyBounds);
		debugShape.setOrigin(0, 0);																																								// offset 0,0 as we are matching physics exactly.
		debugShape.setPosition(GetActorLocation().x ,GetActorLocation().y );

		float rotationDegrees = RadiansToDegrees(_physicsBody->GetAngle());
		debugShape.setRotation(rotationDegrees);

		debugShape.setFillColor(sf::Color::Transparent);
		debugShape.setOutlineColor(sf::Color::Red);
		debugShape.setOutlineThickness(1.0f);

		window.draw(debugShape);
	}
}