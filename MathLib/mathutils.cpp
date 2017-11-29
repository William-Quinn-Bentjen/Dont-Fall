#include "mathutils.h"
#include<time.h>
#include<stdlib.h>

int min(int a, int b)
{
	return a < b ? a : b;
	//same as
	/*
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
	*/
}

void seedRNG()
{
	srand(time(NULL));
}

int RNG(int min, int max)
{
	int range = abs(max - min);
	return rand() % range + min;
}

float gravityFeet(float velocity, float height, float time)
{
	//USE FEET
	//-16x^2 + bx + c
	return -16 * (time) * (time)+velocity * time + height;
}
float gravityMeters(float velocity, float height, float time)
{
	//USE METERS
	//-16x^2 + bx + c
	return -4.9 * (time) * (time)+velocity * time + height;
}