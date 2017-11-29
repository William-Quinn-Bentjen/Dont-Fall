#include "Meteor.h"
#include <iostream>

void Meteor::spawn(float x)
{
	if (used + cooldown <= sfw::getTime())
	{
		transform.pos = { x, 1500 };
		spawned = true;
		used = sfw::getTime();
	}
}

void Meteor::update(float x, int playerAction)
{
	if (spawned == true)
	{
		//move
		transform.pos.y -= 10;
		//check to see if out of screen
		if (transform.pos.y <= -600)
		{
			//off screen
			spawned = false;

		}
		else
		{
			//draw if not out of screen
			sfw::drawTexture(sfw::loadTextureMap("meteorresize.png"), transform.pos.x, transform.pos.y + 139, 375, 646);
		}
	}
	else
	{
		//spawn meteor
		if (playerAction == 9)
		{
			spawn(x);
		}
	}
}

Meteor::Meteor()
{
	spawned = false;
	cooldown = 10;
	used = -10;
}
