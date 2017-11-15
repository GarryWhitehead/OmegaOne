#include "movement.h"

void Serialise(Archive* arch, MoveComponent& sprite, const var_info& info)
{
	Serialise(arch, sprite.m_is_moving, var_info(info.name + ".m_pos"));
	Serialise(arch, sprite.m_velocity, var_info(info.name + ".m_dim"));
	Serialise(arch, sprite.m_xdir, var_info(info.name + ".m_rotation"));
	Serialise(arch, sprite.m_ydir, var_info(info.name + ".m_frame_index"));
}