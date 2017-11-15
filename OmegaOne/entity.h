#ifndef _ENTITY_H
#define _ENTITY_H
#include <unordered_map>
#include <memory>
#include "serialisation.h"

class Entity; 

using EntityPtr = std::shared_ptr<Entity>;

extern void Serialise(Archive *arch, Entity& e, const var_info& info);

class Entity
{
public:

	Entity() : m_comp_handle(0), m_unique_id(0), m_active(true) {}
	Entity(uint32_t ID) : m_comp_handle(0), m_unique_id(ID), m_active(true) {}
	Entity(uint32_t ID, uint32_t comp) : m_comp_handle(comp), m_unique_id(ID), m_active(true) {}

	// helper functions
	uint32_t GetUniqueID() const { return m_unique_id; };
	uint32_t GetComponentBits() const { return m_comp_handle; }
	bool IsActive() const { return m_active;  }

	// functions for serialisation of entity data
	friend void Serialise(Archive *arch, Entity& e, const var_info& info);

private:

	uint32_t m_comp_handle;
	uint32_t m_unique_id;
	bool m_active;
};

static void Serialise(Archive *arch, Entity& e, const var_info& info)
{
	Serialise(arch, e.m_active, var_info(info.name + ".m_active"));
	Serialise(arch, e.m_comp_handle, var_info(info.name + "m_component_ref"));
	Serialise(arch, e.m_unique_id, var_info("m_components"));
}

#endif // _GAMEOBJECT