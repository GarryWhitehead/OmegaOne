#version 330 core

uniform sampler2D tex_unit;

in vec2 tex_coords;

out vec4 frag_colour;

void main()
{
	frag_colour = texture(tex_unit, tex_coords);
}