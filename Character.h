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
	Character(const char* filename, Vec3 pos, Vec3 ro, Vec3 s);
	~Character();

	virtual void Update();
	virtual void Render();
protected:
	void Move();
protected:
	Weapon* _weapon;
	Vec3 _moveDirection;
	double _moveSpeed = 2.5;
};

#endif