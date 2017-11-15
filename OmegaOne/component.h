#ifndef _COMPONENT_H
#define _COMPONENT_H
#include <memory>
#include <vector>
#include "serialisation.h"

class System;
class Component;

using CompPtr = std::shared_ptr<Component>;

// This is a bit of a hack to get this working with serialisation - should be using enums
// TODO: write own enum class which is serialised
static uint32_t POSITION_COMPONENT = 0;
static uint32_t PHYSICS_COMPONENT = 1;
static uint32_t MOVEMENT_COMPONENT = 2;
static uint32_t AI_COMPONENT = 3;
static uint32_t SPRITE_COMPONENT = 4;
static uint32_t ANIMATION_COMPONENT = 5;
static uint32_t GRAPHIC_COMPONENT = 6;
static uint32_t IS_ACTIVE = 7;
static uint32_t NO_COMPONENT = 8;


class Component
{
public:

	Component() : m_type(NO_COMPONENT) {}
	virtual ~Component() {}

	void AddObserver(System *system);
	void RemoveObserver(System *system);
	void Notify();

	// helper functions
	uint32_t ComponentType() { return m_type; }

	// required to allow serilisation function access to protected data members
	friend void Serialise(Archive *arch, Component& comp, const var_info& info);

protected:

	virtual void pack_unpack(Archive *arch, const var_info& info);

	uint32_t m_type;

	std::vector<System*> m_observers;
};


// derived serialisation class required for component derived classes
template <typename T>
class ArchivableComponent : public Component
{
public:

	ArchivableComponent(T& derived, uint32_t type) : m_derived(derived), Component() {}
	~ArchivableComponent() {}

protected:

	void pack_unpack(Archive *arch, const var_info& info)
	{
		Serialise(arch, m_derived, info);
	}

private:

	T &m_derived;
};

void Serialise(Archive *arch, Component& comp, const var_info& info);


#endif // _COMPONENT_H
