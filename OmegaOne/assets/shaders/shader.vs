#version 420 core
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shader_storage_buffer_object : enable

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 tex_uv;
layout(location = 2) in mat4 model;

//layout(std140, binding = 3) buffer model_buffer
//{
//	mat4 model[];
//};

uniform mat4 projection;

out vec2 tex_coords;

void main()
{

	gl_Position = projection * model * vec4(position, 0.0f, 1.0f);
 
	tex_coords = tex_uv;
}
