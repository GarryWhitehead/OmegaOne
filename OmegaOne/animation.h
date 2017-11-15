#ifndef _ANIMATION_H
#define _ANIMATION_H
#include "serialisation.h"
#include "component.h"

struct anim
{
	anim() : frame(0), total(0) {}

	union
	{
		struct
		{
			uint32_t frame;
			uint32_t total;
		};
		uint32_t data[2];
	};
};

//void Serialise(Archive *arch, anim& a, const var_info& info);

class AnimationComponent : public ArchivableComponent<AnimationComponent>
{
public:
	AnimationComponent() : ArchivableComponent<AnimationComponent>(*this, ANIMATION_COMPONENT) {}
	~AnimationComponent() {}

	friend void Serialise(Archive *arch, anim& data, const var_info& info);

private:

	anim m_data;
};



#endif // _ANIMATION_H
