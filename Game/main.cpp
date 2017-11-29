#include<iostream>
#include"sfwdraw.h"
#include"vec2.h"
#include"vec3.h"
#include"player.h"
#include"chasers.h"
#include"mathutils.h"
#include<time.h>
#include<windows.h>
#include "collision.h"
#include "Rigidbody.h"
#include "shapes.h"
#include "drawshapes.h"
#include "collider.h"
#include "Gamemanager.h"

int main()
{
	Game manager;
	bool playAgain = true;
	int winner = 0;
	//runs the tutorial
	winner = manager.tutorial();
	//plays game and loops if they wish to play again
	while (playAgain)
	{
		playAgain = manager.deathscreen(winner);
		if (playAgain == true)
		{
			manager.resetLevel();
			winner = manager.play();
		}
		else if (playAgain == false)
		{
			sfw::termContext();
		}
	}
}