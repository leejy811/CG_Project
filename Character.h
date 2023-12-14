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
	Character(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, double rad, double h, double ms);
	~Character();

	virtual void Init(Vec3 pos, Vec3 ro, Vec3 s, double rad, double h, double ms);
	virtual void Update(double dt);
	virtual void Render();
	virtual void MinimapRender(float red, float green, float blue, float size);
	virtual void OnCollision(CollisonLayer layer, bool isEnter);
public:
	Weapon* _weapon;
	double _curHealth;
	double _maxHealth;
protected:
	void Move(double dt);
	void OnDamage();
protected:
	Vec3 _moveDirection;
	double _moveSpeed;
};

#endif