#ifndef __WEAPON_H__
#define __WEAPON_H__

#pragma once

#include "Object.h"
#include "Bullet.h"

using namespace std;

class Weapon : public Object
{
public:
	Weapon();
	Weapon(const char* filename);
	Weapon(const char* filename, Vec3 pos, Vec3 ro, Vec3 s);
	~Weapon();

	void Update();
	void Render();
	void Shoot(Vec3 playerPos, Vec3 aim);

	vector<Bullet*> _bullets;
protected:
	Vec3 _bulletOffset;
};

#endif