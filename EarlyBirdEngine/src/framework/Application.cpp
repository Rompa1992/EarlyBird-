#include "framework/Application.h"

#include "framework/World.h"
#include "utilities/Core.h"

namespace eb
{
	// Public:
	// =======
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& windowTitle, sf::Uint32 windowStyle)
		: _renderWindow{ sf::VideoMode(windowWidth, windowHeight), windowTitle, windowStyle },
		_currentWorld{ nullptr },
		_tickClock{},
		_targetFrameRate{ 60.f },
		_cleanCycleClock{},
		_cleanCycleInterval{ 2.f }
	{
	}

	// void
	void Application::RunMainLoop()
	{
		/*
		 * Runs the main application loop.
		 * - Processes closing the window.
		 * - Accumulates elapsed time and implements a fixed time step update.
		 * - Ensures game logic (TickInternal) updates consistently at the target frame rate.
		 * - Allows RenderInternal to happen every iteration.
		*/
		
		_tickClock.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / _targetFrameRate;

		while (_renderWindow.isOpen())
		{
			sf::Event windowEvent;
			while (_renderWindow.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
					_renderWindow.close();
			}

			accumulatedTime += _tickClock.restart().asSeconds();												

			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;							// Runs multiple fixed updates if necessary to compensate for frame delays.
				TickInternal(targetDeltaTime);
				RenderInternal();
			}
		}
	}


	/*
	 * Handles creation and initialization of a new World instance.
	 * Returns a weak_ptr to avoid circular references while allowing world access.
	 *
	 * @return weak_ptr to the newly created world
	 * @note World is heap allocated to persist beyond function scope
	*/
	weak_ptr<World> Application::LoadWorld()
	{
		shared_ptr<World> newWorld{ new World{this} };																		// Create a new world instance using a shared_ptr, which ensures proper memory management.
		_currentWorld = newWorld;																							// Update the current world with the newly loaded one.
		_currentWorld->BeginPlayInternal();
		return newWorld;
	}

	// getters
	sf::Vector2u Application::GetWindowSize() const
	{
		return _renderWindow.getSize();
	}

	// Private:
	// ========

	// void
	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		if (_currentWorld)
			_currentWorld->TickInternal(deltaTime);

		// TODO: TimerManager::Get().UpdateTimer(deltaTime);
		// TODO: PhysicsSystem::Get().Step(deltaTime); 

		// Clean Cycle
		if (_cleanCycleClock.getElapsedTime().asSeconds() >= _cleanCycleInterval)
		{
			_cleanCycleClock.restart();
			// TODO: AssetManager::Get().CleanCycle();

			if (_currentWorld)
				_currentWorld->CleanCycle();
		}
	}

	void Application::RenderInternal()
	{
		_renderWindow.clear();
		Render();
		_renderWindow.display();

	}

	// virtual 
	void Application::Tick(float deltaTime)
	{
		 // PRINT_COLOR(CYAN, "deltaTime: %f", deltaTime);
	}

	void Application::Render()
	{
		if (_currentWorld)
			_currentWorld->Render(_renderWindow);
	}
}