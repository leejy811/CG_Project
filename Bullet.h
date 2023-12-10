#ifndef __BULLET_H__
#define __BULLET_H__

#pragma once

#include "Object.h"

using namespace std;

class Bullet : public Object
{
public:
	Bullet();
	Bullet(Vec3 pos, Vec3 ro, Vec3 s, Vec3 target, double rad);
	~Bullet();

	void Init(Vec3 pos, Vec3 ro, Vec3 s, Vec3 target, double rad);
	void Update();
	void Render();
	void OnCollision(CollisonLayer layer, bool isEnter);
public:
	Vec3 targetVec;
	double bulletSpeed = 3;
};

#endif