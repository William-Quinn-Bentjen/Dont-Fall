#pragma once

#include"mat3.h"
class Transform
{
public:
	vec2 pos;
	vec2 dim;
	float angle;
	Transform *e_parent;

	Transform();

	mat3 getLocalTransform() const;
	mat3 getGlobalTransform() const;
};
//void DrawMatrix(const mat3 &t, float drawing_scale);
//void DrawTexture(unsigned sprite, const mat3 &t);