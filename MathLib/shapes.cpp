#include "shapes.h"
#include "mat3.h"
#include "Transform.h"
#include <cmath>
circle operator*(const mat3 & m, const circle & c)
{
	circle ret = c;
	ret.pos = (m*vec3{ c.pos.x, c.pos.y, 1 }).xy;

	vec2 scale;
	scale.x = magnitude(m[0].xy);
	scale.y = magnitude(m[1].xy);
	ret.radius *= fmaxf(scale.x, scale.y);
	return ret;
}

AABB operator*(const mat3 & m, const AABB & b)
{
	
	AABB retval;
	vec2 TL = { b.pos.x - b.extents.x, b.pos.y + b.extents.y };
	vec2 TR = b.pos + b.extents;
	vec2 BL = b.pos - b.extents;
	vec2 BR = { TR.x, BL.y };

	TR = (m * vec3{ TR.x, TR.y, 1 }).xy;
	TL = (m * vec3{ TL.x, TL.y, 1 }).xy;
	BL = (m * vec3{ BL.x, BL.y, 1 }).xy;
	BR = (m * vec3{ BR.x, BR.y, 1 }).xy;
	
	vec2 minCorner = min(TR, min(BL, min(TL, BR)));
	vec2 maxCorner = max(TR, max(BL, max(TL, BR)));;

	retval.pos = (maxCorner + minCorner) / 2;
	retval.extents = (maxCorner - minCorner) / 2;

	return retval;
	
	/*
	//works?
	AABB returnVal;
	Transform c[4];
	//assign these
	vec2 A = b.pos;
	A += b.extents;
	vec2 B = b.pos;
	B -= b.pos;
	vec2 C = b.pos;
	C.x -= b.extents.x;
	C.y += b.extents.y;
	vec2 D = b.pos;
	D.x += b.extents.x;
	D.y -= b.extents.y;

	//Multiply them by matrix
	A = (m * vec3{ A.x,A.y,1 }).xy;
	//b
	B= (m * vec3{ B.x,B.y,1 }).xy;
	//c
	C = (m * vec3{ C.x,C.y,1 }).xy;
	//d
	D = (m * vec3{ D.x,D.y,1 }).xy;

	//Calcualte TR and BL
	float MinminX = fminf(A.x, fminf(B.x, fminf(C.x, D.x)));
	float MinminY = fminf(A.y, fminf(B.y, fminf(C.y, D.y)));
	vec2 MinminVec = { MinminX, MinminY };
	float MaxmaxX = fmaxf(A.x, fmaxf(B.x, fmaxf(C.x, D.x)));
	float MaxmaxY = fmaxf(A.y, fmaxf(B.y, fmaxf(C.y, D.y)));
	vec2 MaxmaxVec = { MaxmaxX, MaxmaxY };

	//Position = (MaxmaxVec + minMinVec) /2
	returnVal.pos = (MaxmaxVec + MinminVec) / 2;
	//extents = (MaxmaxVec - minMinVec) /2
	returnVal.extents = (MaxmaxVec - MinminVec) / 2;
	return returnVal;
	*/

	/*
	mat3 cor[4];
	for (int i = 0; i < 4; ++i)
	{
		c[i].pos = b.pos;
		if (i == 0)
		{
			c[i].pos += b.extents;
		}
		else if (i == 1)
		{
			c[i].pos.y -= b.extents.y;
			c[i].pos.x += b.extents.x;
		}
		else if (i == 2)
		{
			c[i].pos.y -= b.extents.y;
			c[i].pos.x -= b.extents.x;
		}
		else if (i == 3)
		{
			c[i].pos.y += b.extents.y;
			c[i].pos.x -= b.extents.x;
		}
		cor[i].c[2] = { c[i].pos.x, c[i].pos.y, 1 };
		cor[i] = m * cor[i];
	}

	
	vec2 min = b.pos;
	vec2 max = min;
	for (int i = 0; i < 4; ++i)
	{
		if (cor[i].c[2].x > max.x)
		{
			max.x = cor[i].c[2].x;
		}
		if (cor[i].c[2].y > max.y)
		{
			max.y = cor[i].c[2].y;
		}
		if (cor[i].c[2].x < min.x)
		{
			min.x = cor[i].c[2].x;
		}
		if (cor[i].c[2].y < min.y)
		{
			min.y = cor[i].c[2].y;
		}
	}
	
	returnVal.pos.x = ((max.x - min.x) / 2) + min.x;
	returnVal.pos.y = ((max.y - min.y) / 2) + min.y;
	returnVal.extents.x = ((min.x + max.x) / 2);
	returnVal.extents.y = ((min.y + max.y) / 2);
	return returnVal;
	/*
	Transform center;
	center.pos = b.pos;
	Transform c[4];
	for (int i = 0; i < 4; ++i)
	{
		c[i].pos = center.pos;
	}
	c[0].pos += b.extents;
	c[1].pos -= b.extents;
	c[2].pos.x += b.extents.x;
	c[2].pos.y += -b.extents.y;
	c[3].pos.x += -b.extents.x;
	c[3].pos.y += b.extents.y;
	mat3 corners[4];
	for (int i = 0; i < 4; ++i)
	{
		corners[i].c[2] = {c[i].pos.x, c[i].pos.y, 1};
		corners[i] = m * corners[i];
		c[i].pos = corners[i].c[2].xy;
	}
	vec2 min = center.pos;
	vec2 max = min;
	for (int i = 0; i < 4; ++i)
	{
		if (c[i].getGlobalTransform().c[2].x > max.x)
		{
			max.x = c[i].getGlobalTransform().c[2].x;
		}
		if (c[i].getGlobalTransform().c[2].y > max.y)
		{
			max.y = c[i].getGlobalTransform().c[2].y;
		}
		if (c[i].getGlobalTransform().c[2].x < min.x)
		{
			min.x = c[i].getGlobalTransform().c[2].x;
		}
		if (c[i].getGlobalTransform().c[2].y < min.y)
		{
			min.y = c[i].getGlobalTransform().c[2].y;
		}
	}
	AABB returnval;
	returnval.pos.x = ((max.x - min.x) / 2) + min.x;
	returnval.pos.y = ((max.y- min.y) / 2) + min.y;
	returnval.extents.x = ((min.x + max.x) / 2);
	returnval.extents.y = ((min.y + max.y) / 2);

	*/
//	return returnval;

}
