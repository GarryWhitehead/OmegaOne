#include "inputsystem.h"

void InputSystem::Init()
{
	glfwSetKeyCallback(g_engine->m_window, key_callback);
}

void InputSystem::Update(double dt)
{
	glfwPollEvents();
}

void InputSystem::AddEntityRequest(std::unique_ptr<Entity>& e)
{

}

void InputSystem::RemoveEntityFromSystem(int ID)
{

}

void InputSystem::key_callback(GLFWwindow *window, int key, int scan_code, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(g_engine->m_window, GL_TRUE);
		return;
	}
}