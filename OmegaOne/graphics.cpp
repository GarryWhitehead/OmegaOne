#include "graphics.h"
#include <iostream>

GraphicSystem *g_graphics = nullptr;

void GraphicSystem::Init()
{
	g_graphics = this;

	// allocate sprite handler
	m_sprite_handler = std::make_unique<SpriteHandler>();

	// load vertex and fragment shader from file and initialsie
	std::string vert_text, frag_text;
	GLuint vert, frag;
	std::unique_ptr<Shader> shader = std::make_unique<Shader>();
	shader->LoadFile("shader.vs", vert_text);
	shader->LoadFile("shader.fs", frag_text);
	vert = shader->CompileShader(vert_text.c_str(), GL_VERTEX_SHADER);
	frag = shader->CompileShader(frag_text.c_str(), GL_FRAGMENT_SHADER);
	shader->CreateProgram(vert, frag);
	
	shader->Activate();

	// projection matrix used to convert screen co-ords to NDC
	const glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(SCREEN_WIDTH), static_cast<GLfloat>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);
	shader->SetMatrix4("projection", projection);
	shader->SetInteger("image", 0);

	m_shader.insert(std::make_pair("BatchSprite", std::move(shader)));
}

void GraphicSystem::Update(double dt)
{
	m_sprite_handler->Render();
	glfwSwapBuffers(g_engine->Window());
}

void GraphicSystem::AddEntityRequest(std::unique_ptr<Entity>& entity)
{
	// check whether the entities component handle has a graphic element
	uint32_t comp_hand = entity->GetComponentBits();
	uint32_t ID = entity->GetUniqueID();
	if (comp_hand & 1 << static_cast<uint32_t>(GRAPHIC_COMPONENT))
	{
		// add a reference of each entity to that consists of a graphic component to this system
		if ((comp_hand & 1 << SPRITE_COMPONENT))
		{
			auto sprite = g_level->GetComponent<SpriteComponent>(ID, SPRITE_COMPONENT);
			assert(sprite != nullptr);
			// and if the enitiy also contains a active sprite component, add it to out sprite handeler sub-system
			if (!entity->IsActive())
				m_entities.insert(std::make_pair(ID, sprite));
			else
				m_sprite_handler->AddEntityComp<SpriteComponent>(sprite);
		}
	}
}

void GraphicSystem::RemoveEntityFromSystem(int ID)
{

}

std::unique_ptr<Shader>& GraphicSystem::GetShader(std::string name)
{
	return m_shader[name];
}

std::shared_ptr<SpriteComponent>& GraphicSystem::GetSpriteComponent(uint32_t entID)
{
	return m_sprite_handler->GetComponent(entID);
}

void GraphicSystem::UpdateSpriteComponent(uint32_t entID, float x, float y)
{
	m_sprite_handler->UpdateSprite(entID, x, y);
}
