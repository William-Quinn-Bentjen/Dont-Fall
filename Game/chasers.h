#pragma once
#include"vec2.h"
#include"player.h"
class Chaser
{
public:
	bool enabled;
	vec2 pos;
	vec2 targetpos;
};
class CursorChaser : Chaser
{

};
class PlayerChaser : Chaser
{
public:
	float radius;
	PlayerChaser();
	PlayerChaser(float x, float y);
	void update(Player player);
	void draw();
};