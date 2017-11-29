#include "mat3.h"
#include "mathutils.h"
#include <iostream>
#include <assert.h>
bool operator==(const mat3 & a, const mat3 b)
{
	for (int i = 0; i < 9; ++i)
	{
		if (std::abs(a.m[i] - b.m[i]) < EPSILON)
		{
			//number is acceptable
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool operator!=(const mat3 & a, const mat3 b)
{
	return a == b ? false : true;
}

mat3 operator+(const mat3 & a, const mat3 b)
{
	mat3 result;
	for (int i = 0; i < 9; ++i)
	{
		result.m[i] = a.m[i] + b.m[i];
	}
	return result;
}

mat3 operator-(const mat3 & a, const mat3 b)
{
	mat3 result;
	for (int i = 0; i < 9; ++i)
	{
		result.m[i] = a.m[i] - b.m[i];
	}
	return result;
}

mat3 operator*(const mat3 & a, const mat3 b)
{
	mat3 result;
	mat3 at = transpose(a);
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			result.mm[y][x] = dot(at[x], b[y]);
		}
	}
	return result;
	
	/*
				
	for (int i = 0; i < 3; ++i)
	{
		result.mm[i][0] = a.mm[i][0] * b.mm[0][0] + a.mm[i][1] * b.mm[1][0] + a.mm[i][2] * b.mm[2][0];
		result.mm[i][1] = a.mm[i][0] * b.mm[0][1] + a.mm[i][1] * b.mm[1][1] + a.mm[i][2] * b.mm[2][1];
		result.mm[i][2] = a.mm[i][0] * b.mm[0][2] + a.mm[i][1] * b.mm[1][2] + a.mm[i][2] * b.mm[2][2];
	}
	return result;
	*/
}

vec3 operator*(const mat3 & a, const vec3 b)
{
	mat3 at = transpose(a);
	return vec3{ dot(at[0], b),dot(at[1], b),dot(at[2], b) };
	//return a * b;
}

mat3 transpose(const mat3 & a)
{
	mat3 result;
	//result.m[0] = a.m[0];
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			result.mm[i][j] = a.mm[j][i];
		}
	}
	return result;
}

float determinant(const mat3 & a)
{
	return (a.mm[0][0] * a.mm[1][1] * a.mm[2][2]) + (a.mm[0][1] * a.mm[1][2] * a.mm[2][0]) + (a.mm[0][2] * a.mm[1][0] * a.mm[2][1]) - (a.mm[2][2] * a.mm[1][0] * a.mm[0][1]) - (a.mm[2][1] * a.mm[1][2] * a.mm[0][0]) - (a.mm[2][0] * a.mm[1][1] * a.mm[0][2]);
}

mat3 inverse(const mat3 & a)
{
	if (determinant(a) == 0)
	{
		//nothing to do here
		return a;
	}
	float di = 1 / determinant(a);
	mat3 result;
	result.c[0] = cross(a.c[1], a.c[2]) * di;
	result.c[1] = cross(a.c[2], a.c[0]) * di;
	result.c[2] = cross(a.c[0], a.c[1]) * di;
	return transpose(result);
}
/*
0 - X-Axis, right direction
1 - Y-Axis, up direction
2 - Translation, position

*/
mat3 translate(const vec2 & t)
{
	return mat3{ 1,0,0,
				0,1,0,
				t.x,t.y,1 };
	//mat3 result = mat3::identity();
	//result[2].xy = t;
	//return result;
}

mat3 translate(float x, float y)
{
	vec2 pass = { x,y };
	return translate(pass);

	
}

mat3 scale(const vec2 & s)
{
	return mat3{ s.x,0,0,
		         0,s.y,0,
		         0,0,1 };
}

mat3 scale(float x, float y)
{
	vec2 pass = { x,y };
	return scale(pass);
}

vec3 & mat3::operator[](unsigned idx)
{
	//vec3 result = { mm[0][idx], mm[1][idx], mm[2][idx] };
	//return result;
	return c[idx]; // esme
}

const vec3 & mat3::operator[](unsigned idx) const
{
	//vec3 result = { mm[0][idx], mm[1][idx], mm[2][idx] };
	//return result;
	return c[idx]; // esme
}

mat3 mat3::identity()
{
	mat3 result = { 1,0,0,0,1,0,0,0,1 };
	return result;
}
mat3 rotate(float deg)
{
	float rad = deg * 0.0174533;
	return mat3{ cos(rad), sin(rad),0,
				-sin(rad), cos(rad), 0, 
					0, 0, 1 };
}
void checkMat3()
{
	mat3 a = { 1,0,5,2,1,6,3,4,0 };
	mat3 b = { 5,6,1,5,6,1,5,4,8 };
	mat3 c = { 6,6,6,7,7,7,8,8,8 };
	mat3 d = { 30,26,41,45,42,51,35,42,7 };
	vec3 e = { 5,8,6 };
	mat3 f = { 35,0,0,54,0,0,47,0,0 };
	mat3 at = { 1,2,3,0,1,4,5,6,0 };
	mat3 ai = { -24,20,-5,18,-15,4,5,-4,1 };
	assert("3D vector == operator produced an incorrect value", a == a);
	assert("3D vector != operator produced an incorrect value", a != b);
	assert("3D vector + operator produced an incorrect value", a + b == c);
	assert("3D vector - operator produced an incorrect value", c - b == a);
	assert("3D vector * operator produced an incorrect value (matrix * matrix)", a * b  == d);
	assert("3D vector * operator produced an incorrect value (matrix * vector3)", a * e == f);
	assert("3D vector transpose utility produced an incorrect value", transpose(a) == at);
	assert("3D vector determinant utility produced an incorrect value", determinant(a) == 1);
	assert("3D vector inverse utility produced an incorrect value", inverse(a) == ai);
	//SCALE ROTATION AND TRANSLATION
	mat3 T = (scale(vec2{ 1,2 }));
	T = T * rotate(90);
	T = T * translate(vec2{ 3,0 });
	assert((T[2] == vec3{ 0,6,1 }));
	/*
	T = T.identity();
	T = T * translate(vec2{ 3,0 });
	T = (scale(vec2{ 1,2 }));
	T = T * rotate(90);
	*/
	assert((T[2] == vec3{ 0,6,1 }));

	std::cout << "All matrix operator and utility checks successful" << std::endl;
}