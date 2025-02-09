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

		void RunMainLoop();																													// Called in EntryPoint.cpp
		weak_ptr<World> LoadWorld();																										// Called by the game application "weak_ptr<LevelOne> newWorld = LoadWorld<LevelOne>();"

		sf::Vector2u GetWindowSize() const;

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
}