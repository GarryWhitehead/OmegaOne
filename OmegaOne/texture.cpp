#include <iostream>
#include "texture.h"
#include "file_log.h"
#include "glfw3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::~Texture()
{
	Release();
}

// move constructor
Texture::Texture(Texture &&other) : m_data(other.m_data),
									m_textureID(other.m_textureID),
									m_width(other.m_width),
									m_height(other.m_height),
									m_channels(other.m_channels)
{
	other.m_textureID = 0;
	other.m_data = nullptr;
}

// move assignment
Texture& Texture::operator=(Texture&& other)
{
	if (this != &other)
	{
		Release();
		std::swap(m_data, other.m_data);
		std::swap(m_textureID, other.m_textureID);
		m_width = other.m_width; m_height = other.m_height; m_channels = other.m_channels;
	}
}

void Texture::Init()
{
	// bind the texture to the GPU memory
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);

	// texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL error: " << err << "\n";
	}
}

void Texture::LoadTextureFromFile(std::string filename)
{
	std::string path("assets/textures/" + filename);
	m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);
	if (!m_data)
	{
		g_filelog->WriteLog("Critical error! Unable to load texture from file path " + filename);
		exit(EXIT_FAILURE);
	}	
}

void Texture::Release()
{
	glDeleteTextures(1, &m_textureID);
	stbi_image_free(m_data);
	m_data = nullptr;
	m_textureID = 0;
}

