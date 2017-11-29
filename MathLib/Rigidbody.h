#pragma once
#include "vec2.h"
#include "transform.h"
class Rigidbody
{
public:
	float mass;
	vec2 velocity, //speed*direction
		acceleration, // A = F/M
		force, //continuous forces
		impulse;
	float drag;//dampining force

	float angularVel,
		angularAcc,
		torque;
	float angularDrag;


	Rigidbody() : velocity{ 0,0 }, acceleration{ 0,0 }, force{ 0,0 }, impulse{ 0,0 }, mass(1), drag(1), angularVel(0), angularAcc(0), angularDrag(.25f), torque(0)
	{

	}
	void integrate(Transform &t, float dt)
	{
		//linear
		acceleration = force / mass;
		velocity += acceleration * dt + impulse/mass;
		t.pos += velocity *dt;
		impulse = { 0,0 };
		force = -velocity * drag;
		//angular
		angularAcc = torque / mass;
		angularVel += angularAcc;
		t.angle += angularVel * dt;
		torque = -angularVel * angularDrag;
	}
};