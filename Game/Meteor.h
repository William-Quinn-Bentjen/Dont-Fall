#pragma once
#include "Transform.h"
#include "Rigidbody.h"
#include "collider.h"
#include "Controller.h"
#include "sprite.h"
class Meteor
{
public:
	bool spawned; //is the meteor spawned and in screen?
	float used; //when was the last time the player used the meteor
	float cooldown; //how long before they can use the meteor again
	Transform transform; //position, rotation and scale data
	Sprite sprite; //meteor image
	void spawn(float x); //spawns the meteor
	void update(float x, int playerAction); //move the meteor and determine it is off screen (determines spawned)
	Meteor();
};