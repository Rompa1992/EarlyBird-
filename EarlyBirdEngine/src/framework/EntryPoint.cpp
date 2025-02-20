#include "framework/EntryPoint.h"

#include "framework/Application.h"

/// <summary>
/// 
/// Welcome to the Early Bird engine. Written by Nathan Rompa as a learning project. 
/// 
/// NOTE: In comments above sections of code that I tested for semantic errors, 
///		  I have used (++) to denote that I have tested this section and that it is currently working as intended, as far as I know.  
/// 
/// </summary>

int main()
{
	eb::Application* application = GetApplication();
	application->RunMainLoop();

	delete application;
}