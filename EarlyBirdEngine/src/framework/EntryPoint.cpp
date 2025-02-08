#include "framework/EntryPoint.h"

#include "framework/Application.h"

int main()
{
	eb::Application* application = GetApplication();
	application->RunMainLoop();

	delete application;
}