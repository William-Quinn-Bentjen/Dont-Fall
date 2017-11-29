#pragma once
union vec2
{
	// access by array
	float v[2];

	// access by individual component
	struct { float x, y; };

	//subscript opertors
	float operator[](unsigned i)const;
	float &operator[](unsigned i);
};
// arithmetic operators

vec2 operator+(const vec2 &lhs, const vec2 &rhs);
vec2 operator-(const vec2 &lhs, const vec2 &rhs);
vec2 operator*(const vec2 &lhs, float multiplyer);
vec2 operator*(float multiplyer, const vec2 &rhs);
vec2 operator/(const vec2 &lhs, float  divisor);
vec2 operator-(const vec2 &rhs);

// compound assignment operators

vec2 &operator+=(vec2 &lhs, const vec2 &rhs);
vec2 &operator-=(vec2 &lhs, const vec2 &rhs);
vec2 &operator*=(vec2 &lhs, float multiplyer);
vec2 &operator/=(vec2 &lhs, float divisor);

// logical operators

bool operator==(const vec2 &lhs, const vec2 &rhs);
bool operator!=(const vec2 &lhs, const vec2 &rhs);

//Utility Functions

//returns magnitude of a vector
float magnitude(const vec2 vector);
//returns normalized version of a vector
vec2 normal(const vec2 vector);
//normalizes a vector
vec2 &normalize(vec2 &vector);
//returns dot product of two vectors (note that it uses the formula)
//a · b = ax × bx + ay × by
float dot(const vec2 a, const vec2 b);
//returns distance between two points located at the end of a vector 
float distance(const vec2 lhs, const vec2 rhs);
//returns a vector perpendicular to the one input
vec2 perpendicular(const vec2 vector);
//returns a lineraly blended vector between the start and end vector at an alpha (alpha should be between 0 and 1)
vec2 lerp(vec2 start, vec2 end, float alpha);
//returns min values of both vectors
vec2 min(const vec2 a, const vec2 b);
//returns max values of both vectors
vec2 max(const vec2 a, const vec2 b);
//check operators and utility functions
void checkVec2();

//new funcs not checked by checkvec2
vec2 project(const vec2 &v, const vec2 &axis);
vec2 reflect(const vec2 &v, const vec2 &axis);