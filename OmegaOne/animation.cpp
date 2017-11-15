#include "serialisation.h"
#include "animation.h"

void Serialise(Archive *arch, anim& a, const var_info& info)
{
	Serialise(arch, a.data[0], var_info(info.name + ".frame"));
	Serialise(arch, a.data[1], var_info(info.name + ".total"));
}