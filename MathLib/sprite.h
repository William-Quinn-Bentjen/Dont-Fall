#pragma once
#include "vec2.h"
#include "Transform.h"
#include "sfwdraw.h"
class Sprite
{
public:
	int handle;
	vec2 dim;
	vec2 offset;
	Sprite(int a_handle=-1, float width=1, float height=1) : handle(a_handle), dim{ width, height }, offset{ 0,0 }
	{

	}
	void draw(const Transform &t, const mat3 &cam = mat3::identity())
	{
		mat3 M = cam * t.getGlobalTransform() * translate(offset) *  scale(dim);
		sfw::drawTextureMatrix3(handle, 0, WHITE, M.m);
	}
};