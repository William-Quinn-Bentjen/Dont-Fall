#include "vec2.h"
#include "mathutils.h"
#include <cmath>
#include <cfloat>
#include <iostream>
#include <assert.h>


vec2 operator+(const vec2 & lhs, const vec2 & rhs)
{
	return {lhs.x + rhs.x, lhs.y + rhs.y};
}

vec2 operator-(const vec2 & lhs, const vec2 & rhs)
{
	return{ lhs.x - rhs.x, lhs.y - rhs.y };
}

vec2 operator*(const vec2 & lhs, float multiplyer)
{
	return{ lhs.x * multiplyer, lhs.y * multiplyer };
}

vec2 operator*(float multiplyer, const vec2 & rhs)
{
	return{ rhs.x * multiplyer, rhs.y * multiplyer };
}

vec2 operator/(const vec2 & lhs, float divisor)
{
	return{ lhs.x / divisor,lhs.y / divisor };
}

vec2 operator-(const vec2 & rhs)
{
	return{ 0 - rhs.x, 0 - rhs.y };
}

vec2 & operator+=(vec2 & lhs, const vec2 & rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

vec2 & operator-=(vec2 & lhs, const vec2 & rhs)
{
	lhs = lhs - rhs;
	return lhs;
}

vec2 & operator*=(vec2 &lhs, float multiplyer)
{
	lhs.x = lhs.x * multiplyer;
	lhs.y = lhs.y * multiplyer;
	return lhs;
}

vec2 & operator/=(vec2 & lhs, float divisor)
{
	lhs.x = lhs.x / divisor;
	lhs.y = lhs.y / divisor;
	return lhs;
}

bool operator==(const vec2 & lhs, const vec2 & rhs)
{
	// this isn't quite right, but game engines tend
	// to do something fairly close to this process
	//
	// floating-point math is weird! check this out!
	// http://floating-point-gui.de/errors/comparison/
	const int qty = (sizeof(lhs.v) / sizeof(lhs.v[0]));
	for (int i = 0; i < qty; ++i)
	{
		// is the discrepancy within acceptable limits?
		if (std::abs(lhs.v[i] - rhs.v[i]) < EPSILON)
		{
			return true;
		}
	}

	return false;
}

bool operator!=(const vec2 & lhs, const vec2 & rhs)
{
	return (lhs == rhs ? false : true);
}

float magnitude(const vec2 vector)
{
	return sqrt(vector.x*vector.x + vector.y*vector.y);
}

vec2 normal(vec2 vector)
{
	float m = magnitude(vector);
	vector /= m;
	return vector;
}

vec2 &normalize(vec2 &vector)
{
	vector = normal(vector);
	return vector;
}

float dot(const vec2 a, const vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

float distance(const vec2 lhs, const vec2 rhs)
{
	return sqrtf((lhs.x - rhs.x)*(lhs.x - rhs.x) + (lhs.y - rhs.y)*(lhs.y - rhs.y));
}

vec2 perpendicular(const vec2 vector)
{
	//clockwise
	vec2 returnVec = vector;
	returnVec.x = vector.y;
	returnVec.y = vector.x * -1;
	return returnVec;
}

vec2 lerp(vec2 start, vec2 end, float alpha)
{
	vec2 returnVec;
	returnVec.x = start.x + (alpha *(end.x - start.x));
	returnVec.y = start.y + (alpha *(end.y - start.y));
	//returnVec.x = (end.x - start.x)*alpha + start.x;
	//returnVec.y = (end.y - start.y)*alpha + start.y;
	return returnVec;
}

vec2 min(const vec2 a, const vec2 b)
{
	vec2 returnVal;
	if (a.x < b.x)
	{
		returnVal.x = a.x;
	}
	else
	{
		returnVal.x = b.x;
	}
	if (a.y < b.y)
	{
		returnVal.y = a.y;
	}
	else
	{
		returnVal.y = b.y;
	}
	return returnVal;
}

vec2 max(const vec2 a, const vec2 b)
{
	vec2 returnVal;
	if (a.x > b.x)
	{
		returnVal.x = a.x;
	}
	else
	{
		returnVal.x = b.x;
	}
	if (a.y > b.y)
	{
		returnVal.y = a.y;
	}
	else
	{
		returnVal.y = b.y;
	}
	return returnVal;
}

void checkVec2()
{
	//7,1
	vec2 vecA = { 7,1 };
	//3,2
	vec2 vecB = { 3,2 };
	vec2 vecC;
	//arithmetic operators
	vecC = vecA + vecB;
	assert(("2D vector + operator produced an incorrect value", vecC.x == 10 && vecC.y == 3));
	assert(("2D vector - operator produced an incorrect value", vecC - vecB == vecA));
	vecA = { 2,2 };
	vecB = { 6,6 };
	vecC = vecA * 3;
	assert(("2D vector * operator produced an incorrect value (vector, float)", vecC == vecB));
	vecC = 3 * vecA;
	assert(("2D vector * operator produced an incorrect value (float, vector)", vecC == vecB));
	vecB = vecC / 3;
	assert(("2D vector / operator produced an incorrect value", vecB == vecA));
	vecB = vecC * -1;
	assert(("2D vector - operator produced an incorrect value (negitive not subtraction)", vecC == -vecB));
	//common logical operators
	vecA = { 6,6 };
	vecB = { 6,6 };
	vecC = { 7,8 };
	assert(("2D vector == operator produced an incorrect value", vecA == vecB));
	assert(("2D vector != operator produced an incorrect value", vecA != vecC));
	//compound assignment operators
	vecC = { 12,12 };
	vecA += vecB;
	assert(("2D vector += operator produced an incorrect value", vecA == vecC));
	vecA -= vecB;
	assert(("2D vector -= operator produced an incorrect value", vecA == vecB));
	vecA *= 2;
	assert(("2D vector *= operator produced an incorrect value", vecA == vecC));
	vecA /= 2;
	assert(("2D vector /= operator produced an incorrect value", vecA == vecB));
	//utility functions
	vecA = { 0,1 };
	vecB = { 0,1 };
	normalize(vecA);
	assert(("2D vector normalize utility produced an incorrect value", vecA == vecB));
	assert(("2D vector normal utility produced an incorrect value", normal(vecA) == normalize(vecB)));
	assert(("2D vector magnitude utility produced an incorrect value", magnitude(vecA) == 1));
	vecA = { 2,3 };
	vecB = { 7,5 };
	assert(("2D vector dot utility produced an incorrect value", dot(vecA, vecB) == 29));
	vecA = { 5,12 };
	vecB = { 0,0 };
	assert(("2D vector distance utility produced an incorrect value", distance(vecA, vecB) == 13));
	vecA = { -5,-12 };
	vecB = { -12,5 };
	assert(("2D vector perpendicular utility produced an incorrect value", perpendicular(vecA) == vecB));
	vecA = { 0,0 };
	vecB = { 0,5 };
	vecC = { 0,2.5 };
	assert(("2D vector lerp utility produced an incorrect value", lerp(vecA, vecB, .5) == vecC));
	vecA = { 4,0 };
	vecB = { 1,-3 };
	vecC = { 1,-3 };
	assert(("2D vector min utility produced an incorrect value", min(vecA, vecB) == vecC));
	vecC = { 4,0 };
	assert(("2D vector max utility produced an incorrect value", max(vecA, vecB) == vecC));
	std::cout << "All 2D vector operator and utility checks successful" << std::endl;
}

vec2 project(const vec2 & v, const vec2 & axis)
{
	return dot(v, axis) * axis;
}

vec2 reflect(const vec2 & v, const vec2 & axis)
{
	return 2 * project(v, axis) - v;
}

float vec2::operator[](unsigned i) const
{
	return v[i];
}

float & vec2::operator[](unsigned i)
{
	return v[i];
}
