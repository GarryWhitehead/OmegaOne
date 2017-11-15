#include "entity.h"
#include "engine.h"
#include "gamestate.h"
#include "sprite.h"
#include "graphics.h"
#include "inputsystem.h"
#include "serialisation.h"
#include "file_log.h"
#include "AIsystem.h"
#include <memory>

int main(int argc, char *argv[])
{
	Engine engine;
	FileLog filelog;

	// Initialise file logging
	if (!filelog.Init("test-log"))
		exit(EXIT_FAILURE);

	// Add all the systems we will be using to the system list
	engine.AddSystem(new GraphicSystem());
	engine.AddSystem(new InputSystem());
	engine.AddSystem(new AISystem());

	// Initialise engine - 1. Opens main window via GLFW and init. 2. Initiates GLAD. 3.Inititlases all systems
	engine.Init();
	
	engine.AddLevel("test");
	engine.SetCurrentLevel("test");

	double dt = 0.0;

	while (!glfwWindowShouldClose(g_engine->Window()))
	{
		engine.Update(dt);
	}

	engine.ShutDown();
}
