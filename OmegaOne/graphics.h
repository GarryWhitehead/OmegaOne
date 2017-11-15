#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <unordered_map>
#include <vector>
#include <memory>
#include "systems.h"
#include "texture.h"
#include "shader.h"
#include "engine.h"
#include "gtc/matrix_transform.hpp"

class GraphicSystem;

extern GraphicSystem *g_graphics;

class GraphicSystem : public System
{
public:

	GraphicSystem() {}
	~GraphicSystem() {}

	void Init() override;
	void Update(double dt) override;
	void AddEntityRequest(std::unique_ptr<Entity>& entity) override;
	void RemoveEntityFromSystem(int ID) override;

	std::unique_ptr<Shader>& GetShader(std::string name);
	std::shared_ptr<SpriteComponent>& GetSpriteComponent(uint32_t entID);
	void UpdateSpriteComponent(uint32_t entID, float x, float y);

	// friends to the graphics class
	friend class Engine;

private:

	std::unique_ptr<SpriteHandler> m_sprite_handler;
	std::unordered_map<std::string, std::unique_ptr<Shader> > m_shader;

	std::unordered_map<uint32_t, std::shared_ptr<Component> > m_entities;

};

#endif // _GRAPHICS_H
