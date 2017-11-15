#ifndef _MOVEMENT_H
#define _MOVEMENT_H
#include "component.h"


	static uint32_t DIR_LEFT = 0;
	static uint32_t DIR_RIGHT = 1;
	static uint32_t DIR_UP = 2;
	static uint32_t DIR_DOWN = 3;
	static uint32_t DIR_NONE = 4;

class MoveComponent : public ArchivableComponent<MoveComponent>
{
public:
	MoveComponent() : ArchivableComponent<MoveComponent>(*this, MOVEMENT_COMPONENT),
						m_is_moving(false),
						m_velocity(0),
						m_xdir(DIR_NONE),
						m_ydir(DIR_NONE)
	{}

	friend class AISystem;
	friend void Serialise(Archive *arch, bool& moving, const var_info& info);
	friend void Serialise(Archive *arch, float& vel, const var_info& info);
	friend void Serialise(Archive *arch, uint32_t& xdir, const var_info& info);
	friend void Serialise(Archive *arch, uint32_t& ydir, const var_info& info);
	friend void Serialise(Archive* arch, MoveComponent& sprite, const var_info& info);

private:

	bool m_is_moving;
	float m_velocity;
	uint32_t m_xdir, m_ydir;

};

#endif