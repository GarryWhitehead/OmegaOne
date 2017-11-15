#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "glad/glad.h"
#include "glfw3.h"

class SpriteHandler;

class Texture
{
public:
	Texture() : m_data(nullptr), 
				m_textureID(0),
				m_width(0),
				m_height(0),
				m_channels(0)
				{}
	~Texture();

	void Init();
	void LoadTextureFromFile(std::string filename);
	void Release();

	// ensure that the copy contructor and copy assignment can not be used
	Texture(Texture&) = delete;
	Texture& operator=(Texture&) = delete;

	// only allow textures to be moved 
	Texture(Texture &&other);
	Texture& operator=(Texture&& other);

	// helper functions
	GLuint GetID() { return m_textureID;  }

	// friend to texture class
	friend class SpriteHandler;

protected:
	// pointer to loaded texture 
	unsigned char *m_data;

	// reference ID
	GLuint m_textureID;

	// variables required for loading texture
	int m_width, m_height, m_channels;

};
#endif // _TEXTURE_H

