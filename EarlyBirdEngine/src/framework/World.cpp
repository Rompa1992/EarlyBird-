#include "framework/World.h"

#include "framework/Actor.h"
#include "framework/Application.h"
#include "utilities/Core.h"

namespace eb
{
	World::World( Application* owningApplication )
		: _owningApplication{ owningApplication },
		_hasBeganPlay{ false },
		_actors{},
		_pendingActors{}
	{
	}

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

	void World::CleanCycle()
	{
		/*
		 * TODO: understand this and comment it  
		*/
		for (auto iter = _actors.begin(); iter != _actors.end();)																// CodeExplanations->World.cpp: 'TickInternal()'
		{
			//if (iter->get()->IsPendingDestroy())
			//	iter = _actors.erase(iter);
			//else
				//++iter;
		}
	}

	sf::Vector2u World::GetWindowSize() const
	{
		return _owningApplication->GetWindowSize();
	}

	World::~World()
	{

	}

	// private:
	// ========
	void World::BeginPlay()
	{
		PRINT("World Begin Play");
	}

	void World::Tick(float deltaTime)
	{

	}
}