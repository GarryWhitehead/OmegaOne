#include "AIsystem.h"

void AISystem::Init()
{

}

void AISystem::Update(double dt)
{
	auto& iter = m_components.begin(); auto iter_end = m_components.end();
	for (; iter != iter_end; ++iter)
	{
		std::unordered_map<uint32_t, std::shared_ptr<Component> >::const_iterator inner = iter->second.begin();
		auto inner_end = iter->second.end();
		for (; inner != inner_end; ++inner)
		{ 
			if (inner->first == MOVEMENT_COMPONENT)
				if (std::dynamic_pointer_cast<MoveComponent>(inner->second)->m_is_moving)
					this->UpdatePosition(iter->first, std::dynamic_pointer_cast<MoveComponent>(inner->second));
		
		}
	}
}

void AISystem::UpdatePosition(const uint32_t entID, std::shared_ptr<MoveComponent> comp)
{
	auto sprite = g_graphics->GetSpriteComponent(entID);
	Vec2 pos = sprite->GetXYPosition();
	float vel = comp->m_velocity;

	if (comp->m_xdir != DIR_NONE)
		pos.x += (XDir[comp->m_xdir] * vel);

	if (comp->m_ydir != DIR_NONE)
		pos.y += (YDir[comp->m_ydir] * vel);

	g_graphics->UpdateSpriteComponent(entID, pos.x, pos.y);
}

void AISystem::UpdateDirection(const uint32_t entID)
{

}

void AISystem::AddEntityRequest(std::unique_ptr<Entity>& entity) 
{
	// check whether the entities component handle has a graphic element
	uint32_t comp_hand = entity->GetComponentBits();
	uint32_t ID = entity->GetUniqueID();
	if (comp_hand & 1 << MOVEMENT_COMPONENT)
	{
		// add a reference of each entity to that consists of a graphic component to this system
		if ((comp_hand & 1 << SPRITE_COMPONENT))
		{
			auto sprite = g_level->GetComponent<SpriteComponent>(ID, SPRITE_COMPONENT);
			assert(sprite != nullptr);
			// and if the enitiy also contains a active sprite component, add it to out sprite handeler sub-system
			if (!entity->IsActive())
				m_entities.insert(std::make_pair(ID, sprite));
			else
				m_sprite_handler->AddEntityComp<SpriteComponent>(sprite);
		}
	}
}

void AISystem::RemoveEntityFromSystem(int ID)
{

}