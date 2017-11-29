#pragma once
#include "player.h"
class Game
{
public:
	int fonthandle; //holds font image handle
	int tutorialhandle[7]; //holds images for the tutorial
	Player p1; //player 1
	Player p2; //player 2
	DynamicWall wallarr[8]; //floor array
	DynamicWall wallarr2[8]; //2nd floor array
	Wall sides[3]; //side walls
	Wall killBoundery; //kill boundery
	Game();
	int tutorial(); //starts the turorial
	int play(); //plays game and returns winner
	bool deathscreen(int winner); //screen after a player dies returns whether or not to start the game again
	void resetLevel(); //resets player, meteor and floor data
};