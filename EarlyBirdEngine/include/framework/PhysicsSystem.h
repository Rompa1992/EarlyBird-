#pragma once 

#include "box2d/b2_world.h"
#include "SFML/Graphics.hpp"
#include "utilities/Core.h" 

namespace eb
{
    class Actor;

    /*
     * PhysicsContactListener: A custom contact listener for Box2D physics collisions.
     * Inherits from b2ContactListener to handle collision events.
     */
    class PhysicsContactListener : public b2ContactListener
    {
    public:
        // Called when two fixtures begin to touch
        virtual void BeginContact(b2Contact* contact) override;

        // Called when two fixtures cease to touch
        virtual void EndContact(b2Contact* contact) override;
    };

     /*
      * PhysicsSystem: Manages the physics simulation using Box2D.
      * Handles the physics world, bodies, and collision events.
      */
    class PhysicsSystem
    {
    public:
        // Singleton pattern: Get the instance of the PhysicsSystem
        static PhysicsSystem& Get();

        // Step the physics simulation forward by deltaTime seconds
        void Step(float deltaTime);                                                                                     // Called in the Application.cpp

        b2Body* AddListener(Actor* listener);
        void RemoveListener(b2Body* bodyToRemove);

        // Clean up the physics system (e.g., when the game ends)
        static void CleanUp(); /// TODO: call this

        float GetPhysicsScale() const { return _physicsScale; }
        b2Vec2 GetBodyBounds(Actor* listener) const;
        b2Vec2 GetBodyPosition() const;

    protected:
        // Constructor (protected to enforce singleton pattern)
        PhysicsSystem();

    private:
        void ProcessPendingRemoveListeners();

        // Singleton instance of the PhysicsSystem
        static unique_ptr<PhysicsSystem> _physicsSystem;

        // Box2D physics world
        b2World _physicsWorld;

        float _physicsScale;

        int _velocityIterations;
        int _positionIterations;

        PhysicsContactListener _contactListener;
        Set<b2Body*> _pendingRemovalListeners;
    };
}