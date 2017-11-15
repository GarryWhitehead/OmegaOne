#ifndef _SYSTEMS_H
#define _SYSTEMS_H
#include <string>
#include <unordered_map>
#include "entity.h"

class System
{
public:
	virtual ~System() {}
	System() {}

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void AddEntityRequest(std::unique_ptr<Entity>& e) = 0;
	virtual void RemoveEntityFromSystem(int ID) = 0;

	std::string GetType() const { return m_system_type; };



protected:
	//MessageHandler* m_message;

	std::string m_system_type;

};



#endif // _SYSTEMS_H

