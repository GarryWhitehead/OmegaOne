#include "engine.h"
#include "file_log.h"
#include <memory>
#include <iostream>
#include <string>

static const uint32_t SCREEN_WIDTH = 800;
static const uint32_t SCREEN_HEIGHT = 600;

Engine *g_engine = nullptr;

Engine::Engine() :	m_window_title("OmegaOne v0.1"),
					m_running(true),
					m_current_level(nullptr)
{
	g_engine = this;

}

void glfw_error_callback(int error, const char* description) 
{
	std::cout << "GLFW ERROR: code " << error << "\n Description: " << description << "\n";
}

void Engine::Init()
{
	// initialise GLFW and set up the window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
	{
		g_filelog->WriteLog("Critical error! Failed initialising GLFW. \n");
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_monitor = glfwGetPrimaryMonitor();
	m_vmode = glfwGetVideoMode(m_monitor);

	m_window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, m_window_title, NULL, NULL);
	if (m_window == NULL)
	{
		g_filelog->WriteLog("Critical error! Failed to create GLFW window.");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, 0);

	// Initialise GALD before attempting to use opengl functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		g_filelog->WriteLog("Critical error! Failed to initialize GLAD");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// initialise all systems that are aggregated in the map
	for (auto& sys : m_systems)
	{
		sys->Init();
	}
}

void Engine::Update(double dt)
{
	// Update all systems that are associated with engine
	for (auto& sys : m_systems)
	{
		sys->Update(dt);
	}
}

void Engine::AddLevel(std::string name)
{
	m_levels.insert(std::make_pair(name, std::make_shared<Level>(name)));
}

void Engine::SetCurrentLevel(std::string name)
{
	std::unordered_map<std::string, std::shared_ptr<Level> >::const_iterator iter = m_levels.find(name);
	if (iter == m_levels.end())
	{
		g_filelog->WriteLog("Critical error! Unable to find " + name + "level space in map\n");
		exit(EXIT_FAILURE);
	}
	m_current_level = iter->second;

	// serialise data entity data to memory
	m_current_level->LoadDataToLevel();

	// distribute entities system determined by entity component handle 
	for (auto const& sys : m_systems)
	{
		for (auto& iter = m_current_level->m_entities.begin(); iter != m_current_level->m_entities.end(); ++iter)
		{
			sys->AddEntityRequest(iter->second);
		}
	}
}

std::shared_ptr<Level> Engine::GetLevel(std::string name = "")
{
	if (name != "")
	{
		std::unordered_map<std::string, std::shared_ptr<Level> >::const_iterator iter = m_levels.find(name);
		if (iter == m_levels.end())
		{
			g_filelog->WriteLog("Critical error! Unable to find " + name + "level space in map\n");
			exit(EXIT_FAILURE);
		}
		return iter->second;
	}
	else
		return m_current_level;
}

// Entity control functions
void Engine::DeleteEntity(int ID)
{
	for (auto system : m_systems)
	{
		system->RemoveEntityFromSystem(ID);
	}
}

void Engine::AddSystem(System* system)
{
	m_systems.push_back(system);
	//system->InitObservers();
}

void Engine::ShutDown()
{
	// destroy the levels
	m_levels.clear();
	m_current_level = nullptr;

	// and then the systems
	for (auto& sys : m_systems)
	{
		delete sys;
	}

	// and terminate the window
	glfwTerminate();
}

