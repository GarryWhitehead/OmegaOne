#include "sprite.h"

// Serialise function for vec2 struct
void Serialise(Archive *arch, Vec2& vec, const var_info& info)
{
	Serialise(arch, vec.data[0], var_info(info.name + ".x"));
	Serialise(arch, vec.data[1], var_info(info.name + ".y"));
}

void Serialise(Archive *arch, Dim& dim, const var_info& info)
{
	Serialise(arch, dim.data[0], var_info(info.name + ".w"));
	Serialise(arch, dim.data[1], var_info(info.name + ".h"));
}

void Serialise(Archive* arch, SpriteComponent& sprite, const var_info& info)
{
	Serialise(arch, sprite.m_pos, var_info(info.name + ".m_pos"));
	Serialise(arch, sprite.m_dim, var_info(info.name + ".m_dim"));
	Serialise(arch, sprite.m_rotation, var_info(info.name + ".m_rotation"));
	Serialise(arch, sprite.m_frame_index, var_info(info.name + ".m_frame_index"));
}
