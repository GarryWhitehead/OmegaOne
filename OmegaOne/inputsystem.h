#ifndef _INPUTSYSTEM_H
#define _INPUTSYSTEM_H
#include "systems.h"
#include "engine.h"
#include "glfw3.h"

class InputSystem : public System
{
public:
	InputSystem() {}
	~InputSystem() {}

	void Init() override;
	void Update(double dt) override;
	void AddEntityRequest(std::unique_ptr<Entity>& e) override;
	void RemoveEntityFromSystem(int ID) override;

	static void key_callback(GLFWwindow *window, int key, int scan_code, int action, int mode);

private:

};

#endif

