#pragma once
#include "Transform.h"
#include "Rigidbody.h"
#include "collider.h"
#include "Controller.h"
#include "sprite.h"
#include "Meteor.h"
class Wall //static rigidbody used for kill bounderies and side walls
{
public:
	Transform transform;
	Collider collider;
	Sprite sprite;
	Wall();
};
class DynamicWall : public Wall
{
public:
	int handles[2]; //handles for the unbroken and broken floors

	float respawnTime; //time to respawn
	float destroyTime; //time to break
	float breakTime; //when the block broke or when the trigger to break happened

	bool enabled; //colision enabled
	bool breaking; //is the block being broken by the player

	void destroy(bool instant);
	void update();
	void draw();
	DynamicWall();
};
class Ball // dynamic rigid 
{
public:
	Transform transform;
	Rigidbody rigidbody;
	Collider collider;
	Sprite sprite;
};

class Player // dynamic and player controlled
{
public:
	bool alive; //used to determine if the player is alive
	Transform transform; //holds data about position rotation and scale
	Rigidbody rigidbody;
	Collider collider; 
	Controller controller; //gathers input from controllers
	Sprite sprite; //player's sprite
	Meteor meteor; //all info about that player's meteor
	Player();
};
//player v player collision
void doCollision(Player &player1, Player &player2);

//meteor v player collision
bool doCollision(circle meteorHB, Player &player);

//meteor v floor collision
void doCollision(circle meteorHB, DynamicWall &floor);

//player v floor and wall collision
bool doCollision(Player &player, const Wall &wall);

//ball v player collision
bool doCollision(Ball &ball, const Wall &wall);

//player v ball collision
bool doCollision(Player &player, Ball &ball);