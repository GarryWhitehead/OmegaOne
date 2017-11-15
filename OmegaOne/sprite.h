#ifndef _SPRITE_H
#define _SPRITE_H

#include "component.h"
#include "glm.hpp"

class SpriteComponent;
class SpriteHandler;

struct Vec2
{
	Vec2() : x(0.0f), y(0.0f) {}

	union
	{
		struct
		{
			float x;
			float y;
		};
		float data[2];
	};
};

struct Dim
{
	Dim() : w(0), h(0) {}

	union
	{
		struct
		{
			uint32_t w;
			uint32_t h;
		};
		uint32_t data[2];
	};
};

void Serialise(Archive *arch, Vec2& vec, const var_info& info);
void Serialise(Archive* arch, SpriteComponent& sprite, const var_info& info);
void Serialise(Archive *arch, Dim& dim, const var_info& info);

class SpriteComponent : public ArchivableComponent<SpriteComponent>
{
public:
	SpriteComponent() : ArchivableComponent<SpriteComponent>(*this, SPRITE_COMPONENT) {}
	~SpriteComponent() {}

	// helper functions
	Vec2 GetXYPosition() { return m_pos; }
	Dim GetDimensions() { return m_dim; }

	// friends to class
	friend class SpriteHandler;

	// the serialise functions need to be able to access the private variables
	friend void Serialise(Archive *arch, Vec2& vec, const var_info& info);
	friend void Serialise(Archive *arch, Dim& dim, const var_info& info);
	friend void Serialise(Archive *arch, float& rot, const var_info& info);
	friend void Serialise(Archive *arch, uint32_t& ind, const var_info& info);
	friend void Serialise(Archive *arch, SpriteComponent& sprite, const var_info& info);

private:
	Vec2 m_pos;
	Dim m_dim;
	float m_rotation;
	uint32_t m_frame_index;
};



#endif // _SPRITE_H
