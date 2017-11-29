#pragma once
#include "vec2.h"
union vec3
{
	// access by array
	float v[3];

	// access by individual component
	struct { float x, y, z; };

	//subscript opertors
	float &operator[](unsigned idx);
	float operator[](unsigned idx) const;

	//access vec2
	vec2 xy;
};
// arithmetic operators

vec3 operator+(const vec3 &lhs, const vec3 &rhs);
vec3 operator-(const vec3 &lhs, const vec3 &rhs);
vec3 operator*(const vec3 &lhs, float multiplyer);
vec3 operator*(float multiplyer, const vec3 &rhs);
vec3 operator/(const vec3 &lhs, float  divisor);
vec3 operator-(const vec3 &rhs);

// compound assignment operators

vec3 &operator+=(vec3 &lhs, const vec3 &rhs);
vec3 &operator-=(vec3 &lhs, const vec3 &rhs);
vec3 &operator*=(vec3 &lhs, float multiplyer);
vec3 &operator/=(vec3 &lhs, float divisor);

// logical operators

bool operator==(const vec3 &lhs, const vec3 &rhs);
bool operator!=(const vec3 &lhs, const vec3 &rhs);

//Utility Functions

//returns magnitude of a vector
float magnitude(const vec3 vector);
//returns normalized version of a vector
vec3 normal(const vec3 vector);
//normalizes a vector
vec3 &normalize(vec3 &vector);
//returns dot product of two vectors (note that it uses the formula)
//a · b = ax × bx + ay × by
float dot(const vec3 a, const vec3 b);
//returns distance between two points located at the end of a vector 
float distance(const vec3 lhs, const vec3 rhs);
//returns a lineraly blended vector between the start and end vector at an alpha (alpha should be between 0 and 1)
vec3 lerp(vec3 start, vec3 end, float alpha);
//returns min values of both vectors
vec3 min(const vec3 a, const vec3 b);
//returns max values of both vectors
vec3 max(const vec3 a, const vec3 b);
//returns vector whose componets are clamped between the min and max values
vec3 clamp(vec3 input, vec3 min, vec3 max);
//returns cross product of 2 vectors
vec3 cross(const vec3 &a, const vec3 &b);
//check operators and utility functions
void checkVec3();