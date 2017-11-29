#include "vec3.h"
#include "mathutils.h"
#include <cfloat>
#include <cmath>
#include <iostream>
#include <assert.h>

vec3 operator+(const vec3 & lhs, const vec3 & rhs)
{
	vec3 result;
	result.x = lhs.x + rhs.x;
	result.y = lhs.y + rhs.y;
	result.z = lhs.z + rhs.z;
	return result;
}

vec3 operator-(const vec3 & lhs, const vec3 & rhs)
{
	vec3 result;
	result.x = lhs.x - rhs.x;
	result.y = lhs.y - rhs.y;
	result.z = lhs.z - rhs.z;
	return result;
}

vec3 operator*(const vec3 & lhs, float multiplyer)
{
	vec3 result;
	result.x = lhs.x * multiplyer;
	result.y = lhs.y * multiplyer;
	result.z = lhs.z * multiplyer;
	return result;
}

vec3 operator*(float multiplyer, const vec3 & rhs)
{
	vec3 result;
	result.x = rhs.x * multiplyer;
	result.y = rhs.y * multiplyer;
	result.z = rhs.z * multiplyer;
	return result;
}

vec3 operator/(const vec3 & lhs, float divisor)
{
	vec3 result;
	result.x = lhs.x * divisor;
	result.y = lhs.y * divisor;
	result.z = lhs.z * divisor;
	return result;
}

vec3 operator-(const vec3 & rhs)
{
	return rhs * -1;
}

vec3 & operator+=(vec3 & lhs, const vec3 & rhs)
{
	vec3 result;
	result.x = lhs.x + rhs.x;
	result.y = lhs.y + rhs.y;
	result.z = lhs.z + rhs.z;
	return result;
}

vec3 & operator-=(vec3 & lhs, const vec3 & rhs)
{
	vec3 result;
	result.x = lhs.x - rhs.x;
	result.y = lhs.y - rhs.y;
	result.z = lhs.z - rhs.z;
	return result;
}

vec3 & operator*=(vec3 & lhs, float multiplyer)
{
	vec3 result;
	result.x = lhs.x * multiplyer;
	result.y = lhs.y * multiplyer;
	result.z = lhs.z * multiplyer;
	return result;
}

vec3 & operator/=(vec3 & lhs, float divisor)
{
	vec3 result;
	result.x = lhs.x / divisor;
	result.y = lhs.y / divisor;
	result.z = lhs.z / divisor;
	return result;
}

bool operator==(const vec3 & lhs, const vec3 & rhs)
{
	if (abs(lhs.x - rhs.x) < EPSILON && abs(lhs.y - rhs.y) < EPSILON && abs(lhs.z - rhs.z) < EPSILON)
	{
		return true;
	}
	return false;
}

bool operator!=(const vec3 & lhs, const vec3 & rhs)
{
	if (abs(lhs.x - rhs.x) < EPSILON && abs(lhs.y - rhs.y) < EPSILON && abs(lhs.z - rhs.z) < EPSILON)
	{
		return false;
	}
	return true;
}

float magnitude(const vec3 vector)
{
	return sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

vec3 normal(const vec3 vector)
{
	vec3 result;
	float m = magnitude(vector);
	result = vector / m;
	return result;
}

vec3 & normalize(vec3 & vector)
{
	vector = normal(vector);
	return vector;
}

float dot(const vec3 a, const vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float distance(const vec3 lhs, const vec3 rhs)
{
	return sqrtf(((lhs.x - rhs.x)*(lhs.x - rhs.x) + (lhs.y - rhs.y)*(lhs.y - rhs.y)) + ((lhs.z - rhs.z)*(lhs.z - rhs.z)));
}

vec3 lerp(vec3 start, vec3 end, float alpha)
{
	vec3 result;
	result.x = start.x + (alpha *(end.x - start.x));
	result.y = start.y + (alpha *(end.y - start.y));
	result.z = start.z + (alpha *(end.z - start.z));
	return vec3();
}

vec3 min(const vec3 a, const vec3 b)
{
	vec3 result;
	if (a.x < b.x)
	{
		result.x = a.x;
	}
	else
	{
		result.x = b.x;
	}
	if (a.y < b.y)
	{
		result.y = a.y;
	}
	else
	{
		result.y = b.y;
	}
	if (a.z < b.z)
	{
		result.z = a.z;
	}
	else
	{
		result.z = b.z;
	}
	return result;
}

vec3 max(const vec3 a, const vec3 b)
{
	vec3 result;
	if (a.x > b.x)
	{
		result.x = a.x;
	}
	else
	{
		result.x = b.x;
	}
	if (a.y > b.y)
	{
		result.y = a.y;
	}
	else
	{
		result.y = b.y;
	}
	if (a.z > b.z)
	{
		result.z = a.z;
	}
	else
	{
		result.z = b.z;
	}
	return result;
}

vec3 clamp(vec3 input, vec3 min, vec3 max)
{
	vec3 result;
	for (int i = 0; i < 3; ++i) 
	{
		if (input[i] > min[i])
		{
			result[i] = min[i];
		}
		else if (input[i] < max[i])
		{
			result[i] = max[i];
		}
		else
		{
			result[i] = input[i];
		}
	}
	return result;
}

vec3 cross(const vec3 & a, const vec3 & b)
{
	//yz-zy, zx-xz, xy-yx
	return{ a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x };
}

void checkVec3()
{
	vec3 veca;
	vec3 vecb;
	vec3 vecc;
	veca = { 7,1,4 };
	vecb = { 3,2,1 };
	vecc = { 10,3,5 };
	assert("3D vector + operator produced an incorrect value", veca + vecb == vecc);
	veca = { 2,5,0 };
	vecb = { 4,8,6 };
	vecc = { -2,-3,-6 };
	assert("3D vector - operator produced an incorrect value", veca - vecb == vecc);
	veca = { 2,2,1 };
	vecc = { 6,6,3 };
	assert("3D vector * operator produced an incorrect value (float, vector)", veca * 3 == vecc);
	assert("3D vector * operator produced an incorrect value (vector, float)", 3 * veca == vecc);
	assert("3D vector * operator produced an incorrect value", vecc / 3 == veca);
	veca = { 7,1,4 };
	vecb = { 3,2,1 };
	vecc = { 7,1,4 };
	assert("3D vector == operator produced an incorrect value", veca == vecc);
	assert("3D vector != operator produced an incorrect value", vecb != vecc);
	veca = { 7,1,4 };
	vecb = { 3,2,1 };
	vecc = { 10,3,5 };
	veca += vecb;
	assert("3D vector += operator produced an incorrect value", veca == vecc);
	veca = { 2,5,0 };
	vecb = { 4,8,6 };
	vecc = { -2,-3,-6 };
	veca -= vecb;
	assert("3D vector -= operator produced an incorrect value", veca == vecc);
	veca = { 2,2,1 };
	vecc = { 6,6,3 };
	veca *= 3;
	assert("3D vector *= operator produced an incorrect value", veca == vecc);
	veca = { 6,6,2 };
	vecc = { 3,3,1 };
	veca /= 2;
	assert("3D vector /= operator produced an incorrect value", veca == vecc);
	veca = { 7,4,9 };
	assert("3D vector [] operator produced an incorrect value", veca[1] == 1);
	veca = { 0,1,0 };
	assert("3D vector magnitude utility produced an incorrect value", magnitude(veca) == 1);
	vecc = { 3,4,0 };
	assert("3D vector magnitude utility produced an incorrect value (test 2)", magnitude(veca) == 5);
	veca = { 0,1,0 };
	vecb = { 1,1,1 };
	float expected = .57735;
	vecc = { expected,expected,expected };
	assert("3D vector normal utility produced an incorrect value", normal(vecb) == vecc);
	assert("3D vector normalize utility produced an incorrect value", normalize(veca) == veca);
	veca = { 7,2,4 };
	vecb = { 9,4,7 };
	assert("3D vector dot utility produced an incorrect value", dot(veca, vecb) == 99);
	veca = { 7,2,4 };
	vecb = { 9,4,7 };
	expected = 4.12311;
	assert("3D vector distance utility produced an incorrect value", distance(veca, vecb) == expected);
	veca = { 7,2,4 };
	vecb = { 9,4,7 };
	vecc = { 7,2,4 };
	assert("3D vector min utility produced an incorrect value", min(veca, vecb) == vecc);
	veca = { 7,2,4 };
	vecb = { 9,4,7 };
	vecc = { 9,4,7 };
	assert("3D vector max utility produced an incorrect value", max(veca, vecb) == vecc);
	veca = { 9,3,1 };
	vecb = { 7,2,4 };
	vecc = { 9,4,7 };
	vec3 vecd = { 9,3,4 };
	assert("3D vector clamp utility produced an incorrect value", clamp(veca, vecb, vecc) == vecd);
	std::cout << "All 3D vector operator and utility checks successful" << std::endl;
}

float & vec3::operator[](unsigned idx)
{
	return v[idx];
}

float vec3::operator[](unsigned idx) const
{
	return v[idx];
}
