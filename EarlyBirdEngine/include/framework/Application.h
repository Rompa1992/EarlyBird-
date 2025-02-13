#pragma once 

#include "SFML/Graphics.hpp"
#include "utilities/Core.h"

namespace eb
{
	class World;
	class Application
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& windowTitle,  sf::Uint32 windowStyle);

		void RunMainLoop();																													// Called in EntryPoint.cpp																									// Called by the game application "weak_ptr<LevelOne> newWorld = LoadWorld<LevelOne>();"

		sf::Vector2u GetWindowSize() const;
		float GetTargetFrameRate() const { return _targetFrameRate; }

		template<typename WorldType>
		weak_ptr<WorldType> LoadWorld();

	private:
		/*
		 * Top level tick and render to compute base logic. 
		 * - All private so that other derived classed can NOT call the virtual void versions but can override them. 
		 * - This enforces strict control and only allows the virtual functions to be called via a wrapper from a derived class.
		*/
		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Tick(float deltaTime);
		virtual void Render();																												// Called Through RenderInternal(); ^ RunMainLoop();

		shared_ptr<World> _currentWorld;

		sf::Clock _cleanCycleClock;
		float _cleanCycleInterval;
		
		sf::RenderWindow _renderWindow;
		sf::Clock _tickClock;
		float _targetFrameRate;
	};

	/*
	 * Handles creation and initialization of a new World instance.
	 * Returns a weak_ptr to avoid circular references while allowing world access.
	 *
	 * @return weak_ptr to the newly created world
	 * @note World is heap allocated to persist beyond function scope
	*/

	template<typename WorldType>
	weak_ptr<WorldType> Application::LoadWorld()
	{
		shared_ptr<WorldType> newWorld{ new WorldType{this} };																		// Create a new world instance using a shared_ptr, which ensures proper memory management.
		_currentWorld = newWorld;																									// Update the current world with the newly loaded one.
		_currentWorld->BeginPlayInternal();
		return newWorld;																											// Return a weak_ptr to avoid strong ownership by the caller.
	}
}