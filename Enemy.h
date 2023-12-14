#ifndef __ENEMY_H__
#define __ENEMY_H__

#pragma once

#include "Character.h"

using namespace std;

class Enemy : public Character
{
public:
	Enemy();
	Enemy(const char* filename);
	Enemy(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, Character& tar, double rad, double h, double ms);
	~Enemy();

	void Init(Vec3 pos, Vec3 ro, Vec3 s, Character& tar, double rad, double h, double ms);
	void Update(double dt);
	void Render();
	void MinimapRender(float red, float green, float blue, float size);
	void OnCollision(CollisonLayer layer, bool isEnter);
	void OnDamage();
	void OnDie();
private:
	void UpdateMove();
	void AutoShoot(double dt);
private:
	Character* _target;
	double _shootCoolTime = 5000;
	double _curShootTime;
	bool _isMove = true;
};

#endif