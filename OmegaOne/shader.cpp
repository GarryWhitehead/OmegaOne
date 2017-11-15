#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "shader.h"
#include "graphics.h"
#include "file_log.h"
#include "glfw3.h"
#include "gtc/type_ptr.hpp"

void Shader::LoadFile(const char* filename, std::string& text)
{
	std::string path = "assets/shaders/";
	std::ifstream file;
	std::stringstream shader_stream;

	file.open(path + filename, std::fstream::in);
	if (file.is_open())
	{
		shader_stream << file.rdbuf();
		text = shader_stream.str();
	}
	else
	{
		g_filelog->WriteLog("Critical error! Unable to open shader text file");
		exit(EXIT_FAILURE);
	}

}

GLuint Shader::CompileShader(const char *code, GLenum type)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	int success; 
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char info_log[1024];
		glGetShaderInfoLog(shader, 1024, NULL, info_log);
		g_filelog->WriteLog("Critical Error! Failed to compile shader! \n Error Log: \n");
		g_filelog->WriteLog(info_log);
	}
	return shader;
}

void Shader::CreateProgram(GLuint vert, GLuint frag)
{
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vert);
	glAttachShader(m_ID, frag);
	glLinkProgram(m_ID);

	int success; 
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		char info_log[1024];
		glGetProgramInfoLog(m_ID, 1024, NULL, info_log);
		g_filelog->WriteLog("Critical Error! Failed to create shader program! \n Error Log: \n");
		g_filelog->WriteLog(info_log);
	}

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vert);
	glDeleteShader(frag);
}

void Shader::Activate() 
{ 
	glUseProgram(m_ID); 
}


// Uniform set functions
void Shader::SetFloat(const GLchar *name, GLfloat value)
{
	glUniform1f(glGetUniformLocation(this->m_ID, name), value);
}

void Shader::SetInteger(const GLchar *name, GLint value)
{
	glUniform1i(glGetUniformLocation(this->m_ID, name), value);
}

void Shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y)
{
	glUniform2f(glGetUniformLocation(this->m_ID, name), x, y);
}

void Shader::SetVector2f(const GLchar *name, const glm::vec2 &value)
{
	glUniform2f(glGetUniformLocation(this->m_ID, name), value.x, value.y);
}

void Shader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(glGetUniformLocation(this->m_ID, name), x, y, z);
}

void Shader::SetVector3f(const GLchar *name, const glm::vec3 &value)
{
	glUniform3f(glGetUniformLocation(this->m_ID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(glGetUniformLocation(this->m_ID, name), x, y, z, w);
}

void Shader::SetVector4f(const GLchar *name, const glm::vec4 &value)
{
	glUniform4f(glGetUniformLocation(this->m_ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(this->m_ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}