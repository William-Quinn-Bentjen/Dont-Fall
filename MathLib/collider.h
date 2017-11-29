#pragma once
#include "shapes.h"
#include "Transform.h"
#include "collision.h"
class Collider
{
public:
	AABB box;
	AABB getGlobalBox(const Transform &t) const
	{
		return t.getGlobalTransform() * box;
	}
	Collider(const AABB &a_box = { {0,0},{1,1} }) :box(a_box)
	{

	}
};
Collision collides(const Transform &at, const Collider &ac, const Transform &bt, const Collider &bc);
