#include "collider.h"

Collision collides(const Transform & at, const Collider & ac, const Transform & bt, const Collider & bc)
{
	return isect_AABB(ac.getGlobalBox(at), bc.getGlobalBox(bt));
}
