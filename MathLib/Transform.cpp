#include "Transform.h"



Transform::Transform()
{
	pos = vec2{ 0,0 };
	dim = vec2{ 1,1 };
	angle = 0;
	e_parent = nullptr;
}

mat3 Transform::getLocalTransform() const
{
	return translate(pos) * scale(dim) * rotate(angle);

}
mat3 Transform::getGlobalTransform() const
{
	if (e_parent != nullptr)
	{
		return e_parent->getGlobalTransform() * getLocalTransform();
	}
	else
	{
		return getLocalTransform();
	}
}
//void DrawMatrix(const mat3 & t, float drawing_scale)
//{
//	vec2 posi = t[2].xy;
//	vec2 right_ep = posi + t[0].xy * drawing_scale;
//	vec2 up_ep = posi + t[1].xy * drawing_scale;
//	sfw::drawLine(posi.x, posi.y, right_ep.x, right_ep.y, RED);
//	sfw::drawLine(posi.x, posi.y, up_ep.x, up_ep.y, GREEN);
//	sfw::drawCircle(posi.x, posi.y, drawing_scale / 4);
//	//sfw::drawCircle(up_ep.x, up_ep.y, 5, 10, MAGENTA);
//	//sfw::drawCircle(right_ep.x, right_ep.y, 5, 10, YELLOW);
//	//sfw::drawLine(up_ep.x, up_ep.y, right_ep.x, right_ep.y, 0x0C508Cff);
//}
//
//void DrawTexture(unsigned sprite, const mat3 & t)
//{
//	//float mat[9];
//	sfw::drawTextureMatrix3(sprite, 0, WHITE, t.m);
//}