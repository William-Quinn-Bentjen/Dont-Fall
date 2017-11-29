#pragma once
#include "Transform.h"
#include "Rigidbody.h"
#include "sfwdraw.h"

class Controller
{
public:
	int action;
	int playerIndex;
	bool isGrounded;
	void poll(Rigidbody &rb, const Transform &t)
	{
		if (sfw::getGamepadButton(playerIndex, XBOX360_BUTTON_START))action = 10;
		if (sfw::getGamepadButton(playerIndex, XBOX360_BUTTON_BACK))action = 11;
		if (sfw::getGamepadAxis(playerIndex, XBOX360_AXIS_LSTICK_HORIZONTAL) != 0)rb.force += { sfw::getGamepadAxis(playerIndex, XBOX360_AXIS_LSTICK_HORIZONTAL) * 300, 0};
		if (sfw::getGamepadButton(playerIndex, XBOX360_BUTTON_Y))action = 1;
		if (sfw::getGamepadButton(playerIndex, XBOX360_BUTTON_B))action = 2;
		if (sfw::getGamepadButton(playerIndex, XBOX360_BUTTON_A))action = 3;
		if (sfw::getGamepadButton(playerIndex, XBOX360_BUTTON_X))action = 4;
		if (sfw::getGamepadButton(playerIndex, XBOX360_DPAD_UP))action = 5;
		if (sfw::getGamepadButton(playerIndex, XBOX360_DPAD_RIGHT))action = 6;
		if (sfw::getGamepadButton(playerIndex, XBOX360_DPAD_DOWN))action = 7;
		if (sfw::getGamepadButton(playerIndex, XBOX360_DPAD_LEFT))action = 8;
		if (sfw::getGamepadButton(playerIndex, XBOX360_BUTTON_R))action = 9;
		if (isGrounded == true)
		{
			//jumps if player is on the ground
			if (sfw::getGamepadButton(playerIndex, XBOX360_BUTTON_L))rb.impulse += t.getGlobalTransform()[1].xy * 15;
		}

		if (sfw::getGamepadAxis(playerIndex, XBOX360_AXIS_LSTICK_HORIZONTAL) == 0)
		{
			//slow player
			rb.force += -rb.velocity * 5;
		}
	}
};



void platformer_resolution(vec2 & pos, vec2 &vel, const Collision & hit, bool & isGrounded);