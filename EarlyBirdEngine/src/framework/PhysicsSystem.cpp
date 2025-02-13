#include "framework/PhysicsSystem.h"

#include "box2d/b2_body.h"
#include "box2d/b2_contact.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "framework/Actor.h"
#include "utilities/Math.h"

namespace eb
{
    /*
     * PhysicsContactListener Class
     * =====================================================================================================
     * Handles collision detection and notification between physics bodies in the Box2D world.
     * Manages both the start and end of collisions between actors, triggering appropriate overlap events.
     */

     /**
      * Called when two fixtures begin overlapping. Retrieves the associated actors
      * and notifies them of the collision through their overlap events.
      * @param contact The Box2D contact object containing information about the collision
      */
    void PhysicsContactListener::BeginContact(b2Contact* contact)
    {
        Actor* ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        Actor* ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

        if (ActorA && !ActorA->IsPendingDestroy())
            ActorA->OnActorBeginOverlap(ActorB);

        if (ActorB && !ActorB->IsPendingDestroy())
            ActorB->OnActorBeginOverlap(ActorA);
    }

    /**
     * Called when two fixtures stop overlapping. Retrieves the associated actors
     * and notifies them that the overlap has ended.
     * @param contact The Box2D contact object containing information about the collision
     */
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

    unique_ptr<PhysicsSystem> PhysicsSystem::_physicsSystem{ nullptr };

    /*
     * PhysicsSystem Class
     * ===================================================================================================
     * Manages the Box2D physics world and handles the creation, updating, and destruction
     * of physics bodies. Implements a singleton pattern for global access.
     */
    PhysicsSystem::PhysicsSystem()
        : _physicsWorld{ b2Vec2{ 0.f,0.f } },  // Initialize with zero gravity
        _physicsScale{ 1.f },                   // Default physics scale
        _velocityIterations{ 8 },               // Box2D velocity solving iterations
        _positionIterations{ 3 },               // Box2D position solving iterations
        _contactListener{},
        _pendingRemovalListeners{}
    {
        _physicsWorld.SetContactListener(&_contactListener);
        _physicsWorld.SetAllowSleeping(false);  // Keep bodies always active
    }

    /**
     * Returns the singleton instance of the physics system
     * @return Reference to the physics system instance
    */
    PhysicsSystem& PhysicsSystem::Get()
    {
        if (!_physicsSystem)
            _physicsSystem = std::move(unique_ptr<PhysicsSystem>{new PhysicsSystem});

        return *_physicsSystem;
    }

    /**
     * Updates the physics simulation by the specified time step
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void PhysicsSystem::Step(float deltaTime)
    {
        ProcessPendingRemoveListeners();
        _physicsWorld.Step(deltaTime, _velocityIterations, _positionIterations);
    }

    /**
     * Creates a physics body for the given actor and adds it to the physics world
     * @param listener The actor to create a physics body for.
     * @return Pointer to the created Box2D body, or nullptr if creation fails
     */
    b2Body* PhysicsSystem::AddListener(Actor* listener)
    {
        if (listener->IsPendingDestroy()) return nullptr;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);

        b2Vec2 bodyBounds{};
        b2Vec2 bodyPosition{};

        // GET shape bounds =============================================================================================================

        if (listener->IsRectShape())
        {
            bodyBounds = b2Vec2{ listener->GetActorGlobalRectBounds().width * GetPhysicsScale(), listener->GetActorGlobalRectBounds().height * GetPhysicsScale() };

            bodyPosition = { listener->GetActorLocation().x + (listener->GetActorGlobalRectBounds().width / 2.f), listener->GetActorLocation().y + (listener->GetActorGlobalRectBounds().height / 2.f)};
        }
        else if (listener->IsCircleShape())
        {
            float diameter = std::round(listener->GetActorGlobalRectBounds().width * GetPhysicsScale());  // Round to nearest int
            float radius = diameter / 2.0f;
            bodyBounds = b2Vec2{ radius * 2.f, radius * 2.f };

            bodyPosition = { listener->GetActorLocation().x + radius, listener->GetActorLocation().y + radius };
        }

        // End GET shape bounds =========================================================================================================

        bodyDef.position.Set(bodyPosition.x, bodyPosition.y);
        bodyDef.angle = DegreesToRadians(listener->GetActorRotation());
        b2Body* body = _physicsWorld.CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(bodyBounds.x / 2, bodyBounds.y / 2);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.isSensor = true;

        body->CreateFixture(&fixtureDef);

        return body;
    }

    /**
     * Marks a physics body for removal from the physics world
     * @param bodyToRemove The Box2D body to be removed
     */
    void PhysicsSystem::RemoveListener(b2Body* bodyToRemove)
    {
        _pendingRemovalListeners.insert(bodyToRemove);
    }

    /**
     * Resets the physics system to its initial state
     */
    void PhysicsSystem::CleanUp()
    {
        _physicsSystem = std::move(unique_ptr<PhysicsSystem>{new PhysicsSystem});
    }

    b2Vec2 PhysicsSystem::GetBodyBounds(Actor* listener) const
    {
        if (listener->IsRectShape())
        {
            return b2Vec2{ listener->GetActorGlobalRectBounds().width * GetPhysicsScale(), listener->GetActorGlobalRectBounds().height * GetPhysicsScale() };

        }
        else if (listener->IsCircleShape())
        {
            float radius = listener->GetActorGlobalRectBounds().width * GetPhysicsScale();
            return b2Vec2{ radius , radius };
        }
        else return b2Vec2{};
    }

    b2Vec2 PhysicsSystem::GetBodyPosition() const
    {
        return _physicsWorld.GetBodyList()->GetPosition();
    }
    
    /**
     * Processes and removes any physics bodies that have been marked for removal
     */
    void PhysicsSystem::ProcessPendingRemoveListeners()
    {
        for (auto listener : _pendingRemovalListeners)
            _physicsWorld.DestroyBody(listener);

        _pendingRemovalListeners.clear();
    }
}