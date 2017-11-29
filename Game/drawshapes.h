#pragma once
#include "shapes.h"
//most of this is only used for debuging and isn't used in the release 
void drawCircle(const circle &c);
void drawAABB(const AABB &box, int color);
void DrawVecLine(const vec2 &start, const vec2 &end, int color);
void DrawMatrix(const mat3 &t, float drawing_scale);
void drawBox(const mat3 & m, const AABB & box, int color);