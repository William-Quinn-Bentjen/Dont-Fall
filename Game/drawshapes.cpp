#include "drawshapes.h"
#include "sfwdraw.h"

//most of this is used for debuging and isn't used in the release builds

void drawCircle(const circle & c)
{
	sfw::drawCircle(c.pos.x, c.pos.y, c.radius);
}

void DrawVecLine(const vec2 &start, const vec2 &end, int color)
{
	sfw::drawLine(start.x, start.y, end.x, end.y, color);
}

void drawAABB(const AABB & box, int color)
{
	vec2 BL = { box.pos.x - box.extents.x, box.pos.y - box.extents.y };
	vec2 BR = { box.pos.x + box.extents.x, box.pos.y - box.extents.y };
	vec2 TL = { box.pos.x - box.extents.x, box.pos.y + box.extents.y };
	vec2 TR = { box.pos.x + box.extents.x, box.pos.y + box.extents.y };

	DrawVecLine(BL, BR, color);
	DrawVecLine(BR, TR, color);
	DrawVecLine(TR, TL, color);
	DrawVecLine(TL, BL, color);
}

void DrawMatrix(const mat3 & t, float drawing_scale)
{
	vec2 posi = t[2].xy;
		vec2 right_ep = posi + t[0].xy * drawing_scale;
		vec2 up_ep = posi + t[1].xy * drawing_scale;
		sfw::drawLine(posi.x, posi.y, right_ep.x, right_ep.y, RED);
		sfw::drawLine(posi.x, posi.y, up_ep.x, up_ep.y, GREEN);
		sfw::drawCircle(posi.x, posi.y, drawing_scale / 4);
}

void drawBox(const mat3 & m, const AABB & b, int color)
{
//	AABB retval;
	vec2 TL = { b.pos.x - b.extents.x, b.pos.y + b.extents.y };
	vec2 TR = b.pos + b.extents;
	vec2 BL = b.pos - b.extents;
	vec2 BR = { TR.x, BL.y };

	TR = (m * vec3{ TR.x, TR.y, 1 }).xy;
	TL = (m * vec3{ TL.x, TL.y, 1 }).xy;
	BL = (m * vec3{ BL.x, BL.y, 1 }).xy;
	BR = (m * vec3{ BR.x, BR.y, 1 }).xy;
	DrawVecLine(TR, TL, color);
	DrawVecLine(TL, BL, color);
	DrawVecLine(BR, BL, color);
	DrawVecLine(TR, BR, color);
}