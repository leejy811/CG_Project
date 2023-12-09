#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#pragma once

#include "Object.h"
#include "Weapon.h"

using namespace std;

class Character : public Object
{
public:
	Character();
	Character(const char* filename);
	Character(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, double rad, double h);
	~Character();

	virtual void Update();
	virtual void Render();
	virtual void OnCollision(CollisonLayer layer);

	Weapon* _weapon;
protected:
	void Move();
	void OnDamage();
protected:
	Vec3 _moveDirection;
	double _moveSpeed;
	double _health;
};

#endif