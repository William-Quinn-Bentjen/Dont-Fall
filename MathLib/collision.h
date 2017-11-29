#pragma once
#include "shapes.h"
struct Collision
{
	float penDepth; // IF NEGITIVE, ITS THE DISTANCE between the object
	float handedness; // does a need to move left or right on the axis?
	vec2 axis;

};
Collision isect_1D(float aMin, float aMax, float bMin, float bMax);
Collision isect_AABB(const AABB &a, const AABB &b);
Collision isect_circle(const circle &a, const circle &b);
Collision isect_AABB_circle(const AABB &a, const circle &b);
//inout
void static_resolution(vec2 &pos, vec2 &vel, const Collision &hit, float elasticity = 1.0f);
void dynamic_resolution(vec2 &apos, vec2 &avel, float amass, vec2 &bpos, vec2 &bvel, float bmass, const Collision &hit, float elasticity = 1.0f);