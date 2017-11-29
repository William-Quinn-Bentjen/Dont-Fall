#include "Gamemanager.h"
#include <iostream>
#include "player.h"
#include "drawshapes.h"
Game::Game()
{
	sfw::initContext(1024, 1024);
	sfw::setBackgroundColor(0x87ceebff);
	
	//players setup
	p1.sprite = sfw::loadTextureMap("redChar.png");
	p1.meteor.sprite.handle = sfw::loadTextureMap("meteorResize.png");
	p1.transform.dim = { (float)sfw::getTextureWidth(p1.sprite.handle)/5, (float)sfw::getTextureHeight(p1.sprite.handle)/5 };
	p1.transform.pos = { 400,150 };
	p1.collider.box.extents = { .5,.5 };
	p1.controller.playerIndex = 0;
	p1.rigidbody.drag = 0;

	p2.sprite = sfw::loadTextureMap("blueChar.png");
	p2.meteor.sprite.handle = p1.meteor.sprite.handle;
	p2.transform.dim = { (float)sfw::getTextureWidth(p2.sprite.handle)/5, (float)sfw::getTextureHeight(p2.sprite.handle)/5 };
	p2.transform.pos = { 624,150 };
	p2.collider.box.extents = { .5,.5 };
	p2.controller.playerIndex = 1;
	p2.rigidbody.drag = 0;

	//kill boundery
	killBoundery.transform.pos = { 512, -100 };
	killBoundery.transform.dim = { 1024, 50 };
	killBoundery.collider.box.extents = { .5,.5 };

	//walls on the sides of the screen
	sides[0].transform.pos = { -25,512 };
	sides[0].transform.dim = { 50,10000 };
	sides[0].collider.box.extents = { .5,.5 };

	sides[1].transform.pos = { 512,10490 };
	sides[1].transform.dim = { 1024,50 };
	sides[1].collider.box.extents = { .5,.5 };

	sides[2].transform.pos = { 1049,512 };
	sides[2].transform.dim = { 50,10000 };
	sides[2].collider.box.extents = { .5,.5 };

	//load font and tutorial images
	fonthandle = sfw::loadTextureMap("fontmap.png", 16, 16);

	tutorialhandle[0] = sfw::loadTextureMap("01.jpg");
	tutorialhandle[1] = sfw::loadTextureMap("02.jpg");
	tutorialhandle[2] = sfw::loadTextureMap("03.jpg");
	tutorialhandle[3] = sfw::loadTextureMap("04.jpg");
	tutorialhandle[4] = sfw::loadTextureMap("05.jpg");
	tutorialhandle[5] = sfw::loadTextureMap("06.jpg");
	tutorialhandle[6] = sfw::loadTextureMap("07.jpg");

	//load floor images
	int floorA = sfw::loadTextureMap("floorA.png");
	int floorABreak = sfw::loadTextureMap("floorABreak.png");

	int floorB = sfw::loadTextureMap("floorB.png");
	int floorBBreak = sfw::loadTextureMap("floorBBreak.png");

	int floorX = sfw::loadTextureMap("floorX.png");
	int floorXBreak = sfw::loadTextureMap("floorXBreak.png");

	int floorY = sfw::loadTextureMap("floorY.png");
	int floorYBreak = sfw::loadTextureMap("floorYBreak.png");

	int floorUp = sfw::loadTextureMap("floorUp.png");
	int floorUpBreak = sfw::loadTextureMap("floorUpBreak.png");

	int floorRight = sfw::loadTextureMap("floorRight.png");
	int floorRightBreak = sfw::loadTextureMap("floorRightBreak.png");

	int floorDown = sfw::loadTextureMap("floorDown.png");
	int floorDownBreak = sfw::loadTextureMap("floorDownBreak.png");

	int floorLeft = sfw::loadTextureMap("floorLeft.png");
	int floorLeftBreak = sfw::loadTextureMap("floorLeftBreak.png");

	int wall2texture = sfw::loadTextureMap("wallbreaking.jpg");
	for (int i = 0; i < 8; i++)
	{
		if (i == 0)
		{
			wallarr[i].handles[0] = floorY;
			wallarr[i].handles[1] = floorYBreak;

			wallarr2[i].handles[0] = floorY;
			wallarr2[i].handles[1] = floorYBreak;
		}
		if (i == 1)
		{
			wallarr[i].handles[0] = floorB;
			wallarr[i].handles[1] = floorBBreak;

			wallarr2[i].handles[0] = floorB;
			wallarr2[i].handles[1] = floorBBreak;
		}
		if (i == 2)
		{
			wallarr[i].handles[0] = floorA;
			wallarr[i].handles[1] = floorABreak;

			wallarr2[i].handles[0] = floorA;
			wallarr2[i].handles[1] = floorABreak;
		}
		if (i == 3)
		{
			wallarr[i].handles[0] = floorX;
			wallarr[i].handles[1] = floorXBreak;

			wallarr2[i].handles[0] = floorX;
			wallarr2[i].handles[1] = floorXBreak;
		}
		if (i == 4)
		{
			wallarr[i].handles[0] = floorUp;
			wallarr[i].handles[1] = floorUpBreak;

			wallarr2[i].handles[0] = floorUp;
			wallarr2[i].handles[1] = floorUpBreak;
		}
		if (i == 5)
		{
			wallarr[i].handles[0] = floorRight;
			wallarr[i].handles[1] = floorRightBreak;

			wallarr2[i].handles[0] = floorRight;
			wallarr2[i].handles[1] = floorRightBreak;
		}
		if (i == 6)
		{
			wallarr[i].handles[0] = floorDown;
			wallarr[i].handles[1] = floorDownBreak;

			wallarr2[i].handles[0] = floorDown;
			wallarr2[i].handles[1] = floorDownBreak;
		}
		if (i == 7)
		{
			wallarr[i].handles[0] = floorLeft;
			wallarr[i].handles[1] = floorLeftBreak;

			wallarr2[i].handles[0] = floorLeft;
			wallarr2[i].handles[1] = floorLeftBreak;
		}
		wallarr[i].transform.dim = { 128, 64 };
		wallarr[i].transform.pos = { (128 * (float(i) + 1)) - 64,32 };
		wallarr[i].collider.box.extents = { .5,.5 };
		wallarr[i].transform.angle = 90;
		//wallarr2 set up
		wallarr2[i].transform.dim = { 128, 64 };
		if (i < 2 || i >5)
		{
			wallarr2[i].transform.pos = { (128 * (float(i) + 1)) - 64,300 };
		}
		else
		{
			wallarr2[i].transform.pos = { (128 * (float(i) + 1)) - 64, 568 };
		}
		wallarr2[i].collider.box.extents = { .5,.5 };
		wallarr2[i].transform.angle = 90;
	}
}
int Game::tutorial()
{
	int screen = 0;
	float startpress = sfw::getTime();
	float mindelay = 1;
	while (sfw::stepContext())
	{
		sfw::drawTexture(tutorialhandle[screen], 512,512,1024,1024);
		//grabs controller input from player 1
		p1.controller.poll(p1.rigidbody, p1.transform);
		//is the 2nd player's controller connected?
		if (sfw::getGamepadPresent(1))
		{
			return play();
		}
		if (p1.controller.action == 10)
		{
			if (screen < 6 && startpress + mindelay <= sfw::getTime())
			{
				//next part of tutorial
				screen++;
			}
			else if (screen >= 6 && sfw::getGamepadPresent(1) == true)
			{
				return play();
			}
			
			startpress = sfw::getTime();
		}
		p1.controller.action = 0;
	}
}
int Game::play()
{
	while (sfw::stepContext() && (p1.alive && p2.alive))
	{
		float dt = sfw::getDeltaTime();

		//update controllers input
		p1.controller.poll(p1.rigidbody, p1.transform);
		p2.controller.poll(p2.rigidbody, p2.transform);

		//remove floor 
		for (int i = 0; i < 8; ++i)
		{
			if (p1.controller.action == i + 1)
			{
				wallarr[i].destroy(false);
				wallarr2[i].destroy(false);
				p1.controller.action = 0;
			}
			if (p2.controller.action == i + 1)
			{
				wallarr[i].destroy(false);
				wallarr2[i].destroy(false);
				p2.controller.action = 0;
			}
		}
		p1.meteor.update(p1.transform.pos.x, p1.controller.action);
		p1.controller.action = 0;
		p2.meteor.update(p2.transform.pos.x, p2.controller.action);
		p2.controller.action = 0;
		//update rigid bodies
		p1.rigidbody.integrate(p1.transform, dt);
		p2.rigidbody.integrate(p2.transform, dt);
		p1.controller.isGrounded = false;
		p2.controller.isGrounded = false;
		//collision resolution
		//player vs falling/ killboundery
		if (doCollision(p1, killBoundery))
		{
			p1.alive = false;
		}
		if (doCollision(p2, killBoundery))
		{
			p2.alive = false;
		}
		//player on player
		doCollision(p1, p2);
		//player on walls
		for (int i = 0; i < 3; ++i)
		{
			if (doCollision(p1, sides[i]))
				p1.rigidbody.force.y += -3000;
			if (doCollision(p2, sides[i]))
				p2.rigidbody.force.y += -3000;
		}
		//player on floor
		for (int i = 0; i < 8; i++)
		{
			//walls v player and walls v meteor
			if (wallarr[i].enabled == true)
			{
				doCollision(p1, wallarr[i]);
				doCollision(p2, wallarr[i]);
				if (p1.meteor.spawned)
				{
					circle hit;
					hit.pos = p1.meteor.transform.pos;
					hit.radius = 176;
					doCollision(hit, wallarr[i]);
					doCollision(hit, p1);
					doCollision(hit, p2);

				}
				if (p2.meteor.spawned)
				{
					circle hit;
					hit.pos = p2.meteor.transform.pos;
					hit.radius = 176;
					doCollision(hit, wallarr[i]);
					doCollision(hit, p1);
					doCollision(hit, p2);
				}

			}
			if (wallarr2[i].enabled == true)
			{
				doCollision(p1, wallarr2[i]);
				doCollision(p2, wallarr2[i]);
				if (p1.meteor.spawned)
				{
					circle hit;
					hit.pos = p1.meteor.transform.pos;
					hit.radius = 176;
					doCollision(hit, wallarr2[i]);
				}
				if (p2.meteor.spawned)
				{
					circle hit;
					hit.pos = p2.meteor.transform.pos;
					hit.radius = 176;
					doCollision(hit, wallarr2[i]);
				}
			}
		}
		//player gravity
		if (!p1.controller.isGrounded)
			p1.rigidbody.force.y += -3000;
		if (!p2.controller.isGrounded)
			p2.rigidbody.force.y += -3000;
		//draw players
		p2.sprite.draw(p2.transform);
		p1.sprite.draw(p1.transform);
		for (int i = 0; i < 8; i++)
		{
			wallarr[i].draw();
			wallarr2[i].draw();
		}
	}
	//return the winner of the match
	int winner = 0;
	if (p1.alive == true)
	{
		winner = 1;
	}
	else if (p2.alive == true)
	{
		winner = 2;
	}
	if (winner == 0)
	{
		//tie (will return 0)
	}
	return winner;
}

bool Game::deathscreen(int winner)
{
	while (sfw::stepContext())
	{
		if (winner == 0)
		{
			//tie
			sfw::drawString(fonthandle, "TIE you both died at the same time", 0, 500, 30, 30);
		}
		else if (winner == 1)
		{
			//p1 win
			sfw::drawString(fonthandle, "Player 1 Wins", 0, 500, 78, 78);
			p1.transform.pos = { 512, 300 };
			p1.sprite.draw(p1.transform);
		}
		else if (winner == 2)
		{
			//p2 win
			sfw::drawString(fonthandle, "Player 2 Wins", 0, 500, 78, 78);
			p2.transform.pos = { 512, 300 };
			p2.sprite.draw(p2.transform);
		}

		//replay or quit text
		sfw::drawString(fonthandle, "press BACK to quit", 152, 50, 40, 40);
		sfw::drawString(fonthandle, "press START to play again", 0, 100, 40, 40);

		//update controllers input 
		p1.controller.poll(p1.rigidbody, p1.transform);
		p2.controller.poll(p2.rigidbody, p2.transform);

		//see if START or BACK pressed?
		if (p1.controller.action == 11 || p2.controller.action == 11)
		{
			//quit 
			return false;
		}
		if (p1.controller.action == 10 || p2.controller.action == 10)
		{
			//play again
			return true;
		}
	}
}

void Game::resetLevel()
{
	//player reset
	p1.transform.pos = { 400,150 };
	p1.collider.box.extents = { .5,.5 };
	p1.controller.playerIndex = 0;
	p1.rigidbody.drag = 0;
	p1.meteor.transform.pos = { -1000,-1000 };
	p2.meteor.transform.pos = { -1000,-1000 };
	p1.meteor.used = sfw::getTime() - 10;
	p1.alive = true;
	p1.rigidbody.force = { 0,0 };
	p1.rigidbody.velocity = { 0,0 };
	p1.rigidbody.acceleration = { 0,0 };
	p1.rigidbody.impulse = { 0,0 };
	p2.transform.pos = { 624,150 };
	p2.collider.box.extents = { .5,.5 };
	p2.controller.playerIndex = 1;
	p2.rigidbody.drag = 0;
	p2.meteor.used = sfw::getTime() - 10;
	p2.alive = true;
	p2.rigidbody.force = { 0,0 };
	p2.rigidbody.velocity = { 0,0 };
	p2.rigidbody.acceleration = { 0,0 };
	p2.rigidbody.impulse = { 0,0 };

	//reset floor
	for (int i = 0; i < 8; ++i)
	{
		wallarr[i].enabled = true;
		wallarr[i].breaking = false;
		wallarr2[i].enabled = true;
		wallarr2[i].breaking = false;
	}
}
