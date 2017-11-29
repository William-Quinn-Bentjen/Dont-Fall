#pragma once
#include "vec3.h"
union mat3
{
	//array of vectors
	vec3 c[3];
	//1D
	float m[9];
	//2D
	float mm[3][3];

	vec3 &operator[](unsigned idx); //colomn accessor
	const vec3 &operator[](unsigned idx) const;

	static mat3 identity(); //creates and returns identity matrix
};
bool operator==(const mat3 &a, const mat3 b); 
bool operator!=(const mat3 &a, const mat3 b);
mat3 operator+(const mat3 &a, const mat3 b); //not really used
mat3 operator-(const mat3 &a, const mat3 b); //not really used
mat3 operator*(const mat3 &a, const mat3 b); //combine transformations
vec3 operator*(const mat3 &a, const vec3 b); // apply a transformation


//utilities
mat3 transpose(const mat3 &a); //flip rows and colomns
float determinant(const mat3 &a);
mat3 inverse(const mat3 &a);
//
/*
[1 0 X]
[0 1 Y]
[0 0 1]*/
mat3 translate(const vec2 &t);
mat3 translate(float x, float y);
/*
[X 0 0]
[0 Y 0]
[0 0 1] */
mat3 scale(const vec2 &s);
mat3 scale(float x, float y);
/*
a[0] is X axis
a[1] is Y axis

[cos(a) -sin(a) 0]
[sin(a)  cos(a) 0]
[    0       0  1]
*/
mat3 rotate(float deg);
//tests matrix math
void checkMat3();