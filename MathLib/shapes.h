#pragma once
#include "vec2.h"
#include "mat3.h"

struct circle
{
	vec2 pos;
	float radius;
};

//axis alligned bounding box
struct AABB
{
	vec2 pos;
	vec2 extents;

	//four points
	//pos w and h
	//min max corners
	vec2 mn() const { return pos - extents; }
	vec2 mx() const { return pos + extents; }
};

circle operator*(const mat3 &m, const circle &c);
AABB operator*(const mat3 &m, const AABB &b);