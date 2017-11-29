#include "player.h"
#include <iostream>

Player::Player()
{
	alive = true;
}

Wall::Wall()
{
}

void doCollision(Player &player1, Player &player2)
{
	Collision hit = isect_AABB(player1.collider.getGlobalBox(player1.transform), player2.collider.getGlobalBox(player2.transform));
	if (hit.penDepth > 0)
	{
		dynamic_resolution(player1.transform.pos, player1.rigidbody.velocity, player1.rigidbody.mass,
			player2.transform.pos, player2.rigidbody.velocity, player2.rigidbody.mass, hit, .5);
	}
}

bool doCollision(circle meteorHB, Player & player)
{
	Collision hit = isect_AABB_circle(player.collider.getGlobalBox(player.transform), meteorHB);
	if (hit.penDepth > 0)
	{
		player.alive = false;
		return true;
	}
	return false;
}

void doCollision(circle meteorHB, DynamicWall & floor)
{
		Collision hit = isect_AABB_circle(floor.collider.getGlobalBox(floor.transform), meteorHB);
		if (hit.penDepth > 0)
		{
			if (floor.enabled == true)
			{
				floor.destroy(true);
			}
		}
}

bool doCollision(Player & player, const Wall & wall)
{
	auto hit = collides(player.transform, player.collider, wall.transform, wall.collider);
	if (hit.penDepth == 0 && hit.axis.y == -1)
	{
		player.controller.isGrounded = false;
	}
	else if (hit.axis.y == 1 && hit.penDepth >= 0 && player.controller.isGrounded == false)
	{
		//am i above the platform?
		if (player.transform.pos.y - player.transform.dim.y / 2 >= wall.transform.pos.y - wall.transform.dim.y / 2)
		{
		
			player.rigidbody.velocity.y = 0;
			player.controller.isGrounded = true;
		}
		
		else
		{
			player.controller.isGrounded = false;
		}
		
	}

	if (hit.penDepth > 0)
	{
		platformer_resolution(player.transform.pos, player.rigidbody.velocity, hit, player.controller.isGrounded);
		return true;
	}
	return false;
}

bool doCollision(Ball & ball, const Wall & wall)
{
	auto hit = collides(ball.transform, ball.collider, wall.transform, wall.collider);
	if (hit.penDepth > 0)
	{
		static_resolution(ball.transform.pos, ball.rigidbody.velocity, hit, .5);
		return true;
	}
	return false;
}

bool doCollision(Player & player, Ball & ball)
{
	Collision hit = collides(player.transform, player.collider, ball.transform, ball.collider);
	if (hit.penDepth > 0)
	{
		dynamic_resolution(player.transform.pos, player.rigidbody.velocity, player.rigidbody.mass, ball.transform.pos, ball.rigidbody.velocity, ball.rigidbody.mass,hit);
	}
	return false;
}

void DynamicWall::destroy(bool instant)
{
	if (breaking == false)
	{
		if (instant == true)
		{
			enabled = false;
			breaking = false;
			breakTime = sfw::getTime();
		}
		else if (instant == false)
		{
			breakTime = sfw::getTime();
			breaking = true;
		}
	}
}

void DynamicWall::update()
{
	sprite.handle = handles[0];
	if (breaking == true)
	{
		sprite.handle = handles[1];
		if (sfw::getTime() >= breakTime + destroyTime)
		{
			enabled = false;
			breaking = false;
			breakTime = sfw::getTime();
		}
	}
	if (enabled == false)
	{
		if (sfw::getTime() >= breakTime + respawnTime)
		{
			enabled = true;
			breaking = false;
			sprite.handle = handles[0];
		}
	}
}

void DynamicWall::draw()
{
	sprite.handle = handles[0];
	if (breaking == true)
	{
		sprite.handle = handles[1];
		if (sfw::getTime() >= breakTime + destroyTime)
		{
			enabled = false;
			breaking = false;
			breakTime = sfw::getTime();
		}
	}
	if (enabled == false)
	{
		if (sfw::getTime() >= breakTime + respawnTime)
		{
			enabled = true;
			breaking = false;
			sprite.handle = handles[0];
		}
	}
	if (enabled == true)
	{
		sprite.draw(transform);
	}
}

DynamicWall::DynamicWall()
{
	respawnTime = 3;
	destroyTime = 2;
	breakTime = 0;
	enabled = true;
	breaking = false;
}