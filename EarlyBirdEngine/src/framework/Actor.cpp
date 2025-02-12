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
		//PRINT("Actor has began play");
		SetPhysicsEnabled(true);
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
			// Convert position to meters, accounting for center offset
			sf::Vector2f pixelPos(
				GetActorLocation().x + GetActorGlobalRectBounds().width / 2.f,
				GetActorLocation().y + GetActorGlobalRectBounds().height / 2.f
			);

			b2Vec2 meterPos = PhysicsSystem::Get().PixelsToMetersVector(pixelPos);
			float angleRadians = DegreesToRadians(GetActorRotation());

			_physicsBody->SetTransform(meterPos, angleRadians);
		}
	}

	void Actor::RenderDebugPhysics(sf::RenderWindow& window)
	{
		if (!_physicsBody)
			return///ERROR
			// get rid of the pixels to meters. redo physics bodies, create a sure fire test to gurentee accuracy. Figure out why listeners are being added over and over in a loop. 

		sf::RectangleShape debugShape;

		// Use same bounds calculation as physics listener
		if (auto rect = dynamic_cast<sf::RectangleShape*>(_baseShapeActor.get()))
		{
			// Just use original size directly
			debugShape.setSize(rect->getSize());
			debugShape.setOrigin(rect->getOrigin().x + (rect->getSize().x / 2.f),
				rect->getOrigin().y + (rect->getSize().y / 2.f));
		}
		else if (auto circle = dynamic_cast<sf::CircleShape*>(_baseShapeActor.get()))
		{
			float diameter = circle->getRadius() * 2;
			b2Vec2 boundInMeters = PhysicsSystem::Get().PixelsToMetersVector(sf::Vector2f(diameter / 2.f, diameter / 2.f));

			sf::Vector2f pixelBounds = PhysicsSystem::Get().MetersToPixelsVector(boundInMeters);

			debugShape.setSize(sf::Vector2f(pixelBounds.x * 2, pixelBounds.y * 2));
			debugShape.setOrigin(sf::Vector2f{ circle->getOrigin().x + circle->getRadius(),
											 circle->getOrigin().y + circle->getRadius() });
		}

		// Get position from physics body
		b2Vec2 bodyPosition = _physicsBody->GetPosition();
		sf::Vector2f pixelPos = PhysicsSystem::Get().MetersToPixelsVector(bodyPosition);
		debugShape.setPosition(pixelPos);

		// Get rotation from physics body
		float rotationDegrees = RadiansToDegrees(_physicsBody->GetAngle());
		debugShape.setRotation(rotationDegrees);

		debugShape.setFillColor(sf::Color::Transparent);
		debugShape.setOutlineColor(sf::Color::Red);
		debugShape.setOutlineThickness(1.0f);



		window.draw(debugShape);
	}
}