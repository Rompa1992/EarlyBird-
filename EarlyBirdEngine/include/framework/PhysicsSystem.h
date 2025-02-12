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
        void Step(float deltaTime);

        // Add an Actor as a listener to the physics world and return its associated b2Body
        b2Body* AddListener(Actor* listener);

        // Remove a b2Body from the physics world
        void RemoveListener(b2Body* bodyToRemove);

        // Clean up the physics system (e.g., when the game ends)
        static void CleanUp();

        // Get the physics scale (conversion factor between physics units and world units)
        float GetPhysicsScale() const { return _physicsScale; }

        // Convert single values
        float PixelsToMetersValue(float pixels) const;
        float MetersToPixelsValue(float meters) const;

        // convert vectors
        b2Vec2 PixelsToMetersVector(const sf::Vector2f& pixels) const;
        sf::Vector2f MetersToPixelsVector(const b2Vec2& meters) const;

    protected:
        // Constructor (protected to enforce singleton pattern)
        PhysicsSystem();

    private:
        // Process bodies marked for removal from the physics world
        void ProcessPendingRemoveListeners();

        // Singleton instance of the PhysicsSystem
        static unique_ptr<PhysicsSystem> _physicsSystem;

        // Box2D physics world
        b2World _physicsWorld;

        // Scale factor for converting between physics units and world units
        float _physicsScale;

        // Number of velocity iterations for the physics solver (affects accuracy)
        int _velocityIterations;

        // Number of position iterations for the physics solver (affects stability)
        int _positionIterations;

        // Custom contact listener for handling collision events
        PhysicsContactListener _contactListener;

        // Set of bodies marked for removal from the physics world
        Set<b2Body*> _pendingRemovalListeners;
    };
}