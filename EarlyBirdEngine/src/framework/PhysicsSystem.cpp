#include <box2d/b2_body.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

#include "framework/Actor.h"
#include "utilities/Math.h"
#include "framework/PhysicsSystem.h"

namespace eb
{
	/// class PhysicsContactListener
	/// ----------------------------
	void PhysicsContactListener::BeginContact(b2Contact* contact)
	{
		Actor* ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (ActorA && !ActorA->IsPendingDestroy())
			ActorA->OnActorBeginOverlap(ActorB);

		if (ActorB && !ActorB->IsPendingDestroy())
			ActorB->OnActorBeginOverlap(ActorA);
	}

	void PhysicsContactListener::EndContact(b2Contact* contact)
	{
		Actor* ActorA = nullptr;
		Actor* ActorB = nullptr;

		if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
			ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);

		if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
			ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (ActorA && !ActorA->IsPendingDestroy())
			ActorA->OnActorEndOverlap(ActorB);

		if (ActorB && !ActorB->IsPendingDestroy())
			ActorB->OnActorEndOverlap(ActorA);
	}

	// class PhysicsSystem
	// -------------------
	PhysicsSystem::PhysicsSystem()
		: _physicsWorld{ b2Vec2{ 0.f,0.f } },
		_physicsScale{ 1.f },
		_velocityIterations{ 8 },
		_positionIterations{ 3 },
		_contactListener{},
		_pendingRemovalListeners{}
	{
		_physicsWorld.SetContactListener(&_contactListener);
		_physicsWorld.SetAllowSleeping(false);
	}

	unique_ptr<PhysicsSystem> PhysicsSystem::_physicsSystem{ nullptr };

	void PhysicsSystem::Step(float deltaTime)
	{
		ProcessPendingRemoveListeners();
		_physicsWorld.Step(deltaTime, _velocityIterations, _positionIterations);
	}

	b2Body* PhysicsSystem::AddListener(Actor* listener)																											
	{
		if (listener->IsPendingDestroy()) return nullptr;

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;

		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);												

		// NOTE: Physics scale may be causing problems
		bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale() + listener->GetActorGlobalRectBounds().width / 2.f,
			listener->GetActorLocation().y * GetPhysicsScale() + listener->GetActorGlobalRectBounds().height / 2.f);
		bodyDef.angle = DegreesToRadians(listener->GetActorRotation());

		b2Body* body = _physicsWorld.CreateBody(&bodyDef);

		b2PolygonShape shape;
		auto bound = listener->GetActorGlobalRectBounds();
		shape.SetAsBox(bound.width / 2.f * GetPhysicsScale(), bound.height / 2.f * GetPhysicsScale());

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;

		body->CreateFixture(&fixtureDef);

		return body;
	}

	void PhysicsSystem::RemoveListener(b2Body* bodyToRemove)
	{
		_pendingRemovalListeners.insert(bodyToRemove);
	}

	void PhysicsSystem::CleanUp()
	{
		_physicsSystem = std::move(unique_ptr<PhysicsSystem>{new PhysicsSystem});
	}

	PhysicsSystem& PhysicsSystem::Get()
	{
		if (!_physicsSystem)
			_physicsSystem = std::move(unique_ptr<PhysicsSystem>{new PhysicsSystem});												

		return *_physicsSystem;
	}

	// private:
	// ========
	void PhysicsSystem::ProcessPendingRemoveListeners()
	{
		for (auto listener : _pendingRemovalListeners)
			_physicsWorld.DestroyBody(listener);

		_pendingRemovalListeners.clear();
	}
}