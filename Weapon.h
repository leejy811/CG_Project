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
	Weapon(Vec3 pos, Vec3 ro, Vec3 s, Vec3 off);
	~Weapon();

	void Update(double dt);
	void Render();
	void Shoot(Vec3 playerPos, Vec3 aim, bool isAuto);
public:
	vector<Bullet*> _bullets;
	int ammo;
protected:
	Vec3 _bulletOffset;
};

#endif