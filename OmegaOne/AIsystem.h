#ifndef _AISYSTEM_H
#define _AISYSTEM_H
#include <unordered_map>
#include <memory>
#include "systems.h"
#include "component.h"
#include "movement.h"
#include "sprite.h"
#include "graphics.h"

class AISystem : public System
{
public:
	
	static constexpr int32_t XDir[] = { -1, 1, 0 ,0 };
	static constexpr int32_t YDir[] = { 0, 0, -1 ,1 };

	AISystem() {}

	void Init() override;
	void Update(double dt) override;
	void AddEntityRequest(std::unique_ptr<Entity>& entity) override;
	void RemoveEntityFromSystem(int ID) override;

	void UpdatePosition(const uint32_t entID, std::shared_ptr<MoveComponent> comp);
	void UpdateDirection(const uint32_t entID);

protected:

	std::unordered_map<uint32_t, std::unordered_map<uint32_t, std::shared_ptr<Component> > > m_components;
};


class PlayerAISystem : public AISystem
{
public:
	PlayerAISystem() {}

private:


};

#endif
