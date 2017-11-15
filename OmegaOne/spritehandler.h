#ifndef _SPRITEHANDLER_H
#define _SPRITEHANDLER_H
#include <memory>
#include <unordered_map>
#include <vector>
#include <array>
#include "sprite.h"
#include "shader.h"
#include "graphics.h"
#include "texture.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class Texture;

// macro for opengl nasty fucntion calls requiring buffer offset
#define BUFFER_OFFSET(i) ((char *)NULL + (i)) 

class SpriteHandler
{
public:
	SpriteHandler() :	m_active_sprites(0),
						m_vao(0),
						m_is_buffer_generated(false)
						{}

	void GenerateModelBuffer(std::unique_ptr<Texture>& tex);
	void GenerateTexelBuffer(std::unique_ptr<Texture>& tex);
	void InitBuffers();
	void Render();

	template <typename T>
	void AddEntityComp(std::shared_ptr<T> comp);
	std::shared_ptr<SpriteComponent>& GetComponent(uint32_t entID);
	void SpriteHandler::UpdateSprite(uint32_t entID, float x, float y);

	// friends to spritehandler class
	friend class SpriteComponent;
	friend class Texture;

private:

	std::vector<std::shared_ptr<SpriteComponent> > m_batchsprite_data;
	std::vector<std::array<float, 12> > tex_buffer;
	std::vector<glm::mat4> model_buffer;

	int m_active_sprites;
	GLuint m_vao;
	GLuint m_vbo[3];
	bool m_is_buffer_generated;

};

template <typename T>
void SpriteHandler::AddEntityComp(std::shared_ptr<T> comp)
{
	m_batchsprite_data.push_back(comp);
	++m_active_sprites;
}

#endif // _SPRITEHANDLER
