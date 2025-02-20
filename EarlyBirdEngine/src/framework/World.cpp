#include "framework/World.h"

#include "framework/Actor.h"
#include "framework/Application.h"
#include "utilities/Core.h"

namespace eb
{
	// public:
	// =======
	World::World( Application* owningApplication )
		: _owningApplication{ owningApplication },
		_hasBeganPlay{ false },
		_actors{},
		_pendingActors{},
		_isWorldEmptyOfActors{ false }
	{
	}

	// void
	void World::BeginPlayInternal()
	{
		if (!_hasBeganPlay)
		{
			_hasBeganPlay = true;
			BeginPlay();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		// Newly created actors that haven't been initialized yet
		for (shared_ptr<Actor> actor : _pendingActors)
		{
			_actors.push_back(actor);																			// move _pendingActors to _actors List. 													
			actor->BeginPlayInternal();
		}

		_pendingActors.clear();

		// Tick Actors in World
		for (auto iter = _actors.begin(); iter != _actors.end();)																
		{
			iter->get()->TickInternal(deltaTime);																				
			++iter;
		}

		Tick(deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (shared_ptr<Actor> actor : _actors)
			actor->Render(window);
	}

	/*	
	  * Safely removes actors marked for destruction from the world.
	  * Uses iterator-safe removal pattern to avoid invalidation issues.
	  *
	  * Iterator Process:
	  * 1. begin() starts at first actor
	  * 2. If actor should be destroyed:
	  *    - erase() removes it and returns iterator to next actor
	  * 3. If actor stays:
	  *    - manually increment iterator to next actor
	  * 4. Continues until reaching end()
	  *
	  * Note: Don't increment after erase() as it already returns
	  * iterator to next element
	*/

	void World::CleanCycle()
	{

		for (auto iter = _actors.begin(); iter != _actors.end();)																
		{
			if (iter->get()->IsPendingDestroy())
				iter = _actors.erase(iter);																						// erase() returns valid iterator to next element
			else
				++iter;
		}

		if (_actors.empty())
			_isWorldEmptyOfActors = true;
		else
			_isWorldEmptyOfActors = false;
	}

	void World::DestroyAllActors()
	{
		for (auto& actor : _actors)
		{
			actor->Destroy(); 
		}
	}

	// getters
	sf::Vector2u World::GetWindowSize() const
	{
		return _owningApplication->GetWindowSize();
	}

	float World::GetTargetFrameRate() const
	{
		return _owningApplication->GetTargetFrameRate();
	}

	World::~World()
	{
		// Nothing to implement.
	}

	// private:
	// ========
	void World::BeginPlay()
	{
		PRINT("World Begin Play");
	}

	void World::Tick(float deltaTime)
	{
		// Nothing to implement.
	}
}