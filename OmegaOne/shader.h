#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include "glfw3.h"
#include "glm.hpp"

class Shader
{
public:
	
	Shader() : m_ID(0) {}

	void LoadFile(const char* filename, std::string& text);
	GLuint CompileShader(const char *code, GLenum type);
	void CreateProgram(GLuint vert, GLuint frag);
	void Activate();

	// utility uniform functions
	void SetFloat(const GLchar *name, GLfloat value);
	void SetInteger(const GLchar *name, GLint value);
	void SetVector2f(const GLchar *name, GLfloat x, GLfloat y);
	void SetVector2f(const GLchar *name, const glm::vec2 &value);
	void SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
	void SetVector3f(const GLchar *name, const glm::vec3 &value);
	void SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void SetVector4f(const GLchar *name, const glm::vec4 &value);
	void SetMatrix4(const GLchar *name, const glm::mat4 &matrix);

	// helper functions
	unsigned int GetShaderID() { return m_ID; }

private:
	
	GLuint m_ID;

};
#endif

