#include "collision.h"
#include "mathutils.h"
#include "shapes.h"
#include <cmath>
#include <iostream>

Collision isect_1D(float aMin, float aMax, float bMin, float bMax)
{
	Collision retval;
	float lPD = bMax - aMin;
	float rPD = aMax - bMin;
	retval.penDepth = min(lPD, rPD);
	retval.handedness = copysign(1, rPD - lPD);
	return retval;
}

Collision isect_AABB(const AABB & a, const AABB & b)
{
	Collision xres = isect_1D(a.mn().x, a.mx().x, b.mn().x, b.mx().x);
	Collision yres = isect_1D(a.mn().y, a.mx().y, b.mn().y, b.mx().y);
	xres.axis = vec2{ 1,0 };
	yres.axis = vec2{ 0,1 };
	return xres.penDepth < yres.penDepth ? xres : yres;
}

Collision isect_circle(const circle & a, const circle & b)
{
	Collision ret;
	ret.axis = normal(b.pos - a.pos);
	ret.handedness = -1;
	//how do we cal depth?
	float ap = dot(ret.axis, a.pos);
	float bp = dot(ret.axis, b.pos);
	float aMin = ap - a.radius;
	float aMax = ap + a.radius;
	float bMin = bp - b.radius;
	float bMax = bp + b.radius;
	ret.penDepth = isect_1D(aMin, aMax, bMin, bMax).penDepth;
	return ret;
}

Collision isect_AABB_circle(const AABB & a, const circle & b)
{
	circle number2;
	              number2.pos = a.pos;
	if (b.pos.x > a.pos.x + a.extents.x)
	{
		number2.pos.x = a.pos.x + a.extents.x;
	}
	else if (b.pos.x < a.pos.x - a.extents.x)
	{
		number2.pos.x = a.pos.x - a.extents.x;
	}
	if (b.pos.y > a.pos.y + a.extents.y)
	{
		number2.pos.y = a.pos.y + a.extents.y;
	}
	else if (b.pos.y < a.pos.y - a.extents.y)
	{
		number2.pos.y = a.pos.y - a.extents.y;
	}
	number2.radius = 0;
	Collision hit = isect_circle(number2, b);
	return hit;
		
	/*
	return Collision();
	//find the axis (closest point on AABB to circle)
	vec2 TL = { a.pos.x - a.extents.x, a.pos.y + a.extents.y };
	vec2 TR = a.pos + a.extents;
	vec2 BL = a.pos - a.extents;
	vec2 BR = { TR.x, BL.y };
	
	vec2 shortest;
	float shortDist = distance(TL, b.pos);
	if (distance(TR, b.pos) < shortDist)
	{
		shortest = TR;
		shortDist = distance(TR, b.pos);
	}
	if (distance(BR, b.pos) < shortDist)
	{
		shortest = BR;
		shortDist = distance(BR, b.pos);
	}
	if (distance(BL, b.pos) < shortDist)
	{
		shortest = BL;
		shortDist = distance(BL, b.pos);
	}
	//

	Collision ret;
	ret.axis = normal(shortest - b.pos);
	vec2 axisEnd;
	//while()
	//isect_1D()
	//project points of each onto the axis
	//fins min and max of those points for each
	//1d intercetion
	*/
}


void platformer_resolution(vec2 & pos, vec2 &vel, const Collision & hit, bool & isGrounded)
{
	//on top ? ground
	//else static collision
	if (hit.axis.y == 1)
	{
		pos += hit.axis * hit.handedness * hit.penDepth;
	}
	else
	{
		pos += hit.axis * hit.handedness * hit.penDepth;
		vel = -reflect(vel, hit.axis*hit.handedness) * .25;
	}
	//std::cout << "x axis " << hit.axis.x << std::endl << "y axis " << hit.axis.y << "harness " << hit.handedness << std::endl;
	/*if (fabs(hit.axis.y) == 1)
	{
		if (hit.handedness > 0)
		{
			vel.y = 0;
			isGrounded = true;
		}
		else
		{
			vel = -reflect(vel, hit.axis*hit.handedness) * .1;
			//vel.y = -hit.handedness * hit.penDepth;
			std::cout << vel.y << std::endl;
			isGrounded = false;
		}
		
	}
	else if (fabs(hit.axis.x) == 1)
	{
		vel.x = hit.handedness;
		isGrounded = false;
	}
	std::cout << "x axis " << hit.axis.x << std::endl << "y axis " << hit.axis.y << "harness " << hit.handedness << std::endl;
	pos += hit.axis * hit.handedness * hit.penDepth;
	*/
}

void static_resolution(vec2 & pos, vec2 & vel, const Collision & hit, float elasticity)
{
	//correct pos 
	pos += hit.axis * hit.handedness * hit.penDepth;
	//vel reflect
	vel = -reflect(vel, hit.axis*hit.handedness) * elasticity;
}

void dynamic_resolution(vec2 & apos, vec2 & avel, float amass,
						vec2 & bpos, vec2 & bvel, float bmass,
						const Collision & hit, float elasticity)
{
	//law of conservation
	/*
		mass*vel = momentum

		ap + bp = `ap + `bp // conservation of momentum

		avel*amass+ bvel* bmass = favel *amass + fbvel* bmass

		av - bv = -(`fbv -`fav) //relative velocity
		fbvel = Bvel - avel + favel

		avel*amass+ bvel* bmass = favel *amass + fbvel* bmass

		vec2 fav = avel + j
	*/
	vec2 normal = hit.axis * hit.handedness;
	vec2 rvel = avel - bvel;
	
	float j = -(1+ elasticity) * dot(rvel, normal) / dot(normal,normal*(1 / amass + 1 / bmass)); //impulse magnatude -balanced change in magnatude
	
	avel += (j / amass) * normal;
	bvel -= (j / bmass) * normal;
	apos += normal * hit.penDepth * amass / (amass + bmass);
	bpos -= normal * hit.penDepth * bmass / (amass + bmass);
}
