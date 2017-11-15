#ifndef _ENGINE_H
#define _ENGINE_H
#include <vector>
#include <memory>
#include <unordered_map>
#include "entity.h"
#include "spritehandler.h"
#include "gamestate.h"
#include "glad/glad.h"
#include "glfw3.h"

//class Entity;
class System;
class Engine;
class InputSystem;
class Level;

extern Engine *g_engine;

extern const uint32_t SCREEN_WIDTH;
extern const uint32_t SCREEN_HEIGHT;

class Engine
{
public:

	Engine();

	// main core functions
	void Init();
	void Update(double dt);
	void AddSystem(System* system);
	void ShutDown();
	void DeleteEntity(int ID);
	void AddLevel(std::string name);
	void SetCurrentLevel(std::string name);

	// helper functions
	GLFWwindow* Window() { return m_window; }
	std::shared_ptr<Level> GetLevel(std::string name);

	friend class InputSystem;

private:

	// GLFW window variables
	GLFWwindow* m_window;
	const char* m_window_title;
	GLFWmonitor* m_monitor;
	const GLFWvidmode* m_vmode;

	bool m_running;
	std::shared_ptr<Level> m_current_level;

	std::unordered_map<std::string, std::shared_ptr<Level> > m_levels;
	std::vector<System*> m_systems;
};

#endif // _ENGINE_H

