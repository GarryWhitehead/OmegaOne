#include "spritehandler.h"
#include <iostream>

std::shared_ptr<SpriteComponent>& SpriteHandler::GetComponent(uint32_t entID)
{
	return m_batchsprite_data[entID];
}

void SpriteHandler::UpdateSprite(uint32_t entID, float x, float y)
{
	auto iter = m_batchsprite_data[entID];
	iter->m_pos.x = x;
	iter->m_pos.y = y;
}

void SpriteHandler::GenerateTexelBuffer(std::unique_ptr<Texture>& tex)
{
	tex_buffer.clear();
	for (auto& sprite : m_batchsprite_data)
	{
		// first calculate the texcoords for the sprite
		float tex_w = sprite->m_dim.w / static_cast<float>(tex->m_width);
		float tex_h = sprite->m_dim.h / static_cast<float>(tex->m_height);

		int image_per_row = tex->m_width / sprite->m_dim.w;
		float tex_x = (sprite->m_frame_index % image_per_row) * tex_w;
		float tex_y = (sprite->m_frame_index / image_per_row) * tex_h;
		float offset_x = 0.01f / tex_x;
		float offset_y = 0.01f / tex_y;

		std::array<float, 12> tex_pos;
		tex_pos[0] = tex_x; tex_pos[1] = tex_y + tex_h;
		tex_pos[2] = tex_x + tex_w; tex_pos[3] = tex_y;
		tex_pos[4] = tex_x; tex_pos[5] = tex_y;
		tex_pos[6] = tex_x; tex_pos[7] = tex_y + tex_h;
		tex_pos[8] = tex_x + tex_w; tex_pos[9] = tex_y + tex_h;
		tex_pos[10] = tex_x + tex_w; tex_pos[11] = tex_y;
		tex_buffer.push_back(tex_pos);
	}
}

void SpriteHandler::GenerateModelBuffer(std::unique_ptr<Texture>& tex)
{
	model_buffer.clear();

	for (auto& sprite : m_batchsprite_data)
	{
		// setup the matrix transformation buffer
		glm::mat4 model = glm::translate(glm::mat4x4(1.0f), glm::vec3(sprite->m_pos.x, sprite->m_pos.y, 0.0f));

		//rotate around the middle of the texture
		model = glm::translate(model, glm::vec3(0.5f * sprite->m_dim.w, 0.5f * sprite->m_dim.h, 0.0f));
		model = glm::rotate(model, sprite->m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * sprite->m_dim.w, -0.5f * sprite->m_dim.h, 0.0f));

		// and scale the texture
		model = glm::scale(model, glm::vec3(sprite->m_dim.w, sprite->m_dim.h, 1.0f));
		model_buffer.push_back(model);
	}
}


void SpriteHandler::InitBuffers()
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// bind the tex co-ords which will be instanced
	glGenBuffers(1, &m_vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec2) * 6) * tex_buffer.size(), tex_buffer.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(0));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// and finally the model matrix used for each instance is binded to a ssbo
	glGenBuffers(1, &m_vbo[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_vbo[1]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::mat4) * model_buffer.size(), model_buffer.data(), GL_STATIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, m_vbo[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void SpriteHandler::Render()
{

	glClearColor(0.2f, 0.0f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!m_is_buffer_generated)
	{
		this->GenerateTexelBuffer(g_level->GetTexture());
		this->GenerateModelBuffer(g_level->GetTexture());
		this->InitBuffers();
		m_is_buffer_generated = true;
	}
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_vao);
	// Draw all active sprites 
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 6, m_active_sprites);

	GLuint err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL error: " << err << "\n";
	}

}
