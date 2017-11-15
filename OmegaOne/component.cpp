#include "component.h"
#include "sprite.h"
#include "animation.h"

void Initialise()
{

}

void Component::AddObserver(System* system)
{
	m_observers.push_back(system);

}

void Component::RemoveObserver(System *system)
{
	std::vector<System*>::iterator iter;

	for (iter = m_observers.begin(); iter != m_observers.end(); iter++)
	{
		//if((*itr)->getType() == system->getType())
		{
			m_observers.erase(iter);
			break;
		}
	}
}

void Component::Notify()
{
	std::vector<System*>::iterator iter;

	for (iter = m_observers.begin(); iter != m_observers.end(); iter++)
	{
		//(*itr)->HandleMessage(this);
	}

}


// serialisation function
void Serialise(Archive *arch, Component& comp, const var_info& info)
{
	comp.pack_unpack(arch, info);
	//Serialise(arch, static_cast<int32_t>(comp.m_type), var_info(info.name + ".m_type"));
}

void Component::pack_unpack(Archive *arch, const var_info& info)
{}
