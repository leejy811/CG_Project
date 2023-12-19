#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#pragma once

#include "Object.h"
#include "Weapon.h"
#include "Animator.h"

using namespace std;

class Character : public Object
{
public:
	Character();
	Character(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, double rad, double h, double ms);
	~Character();

	virtual void Init(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, double rad, double h, double ms);
	virtual void Update(double dt);
	virtual void Render();
	virtual void MinimapRender(float red, float green, float blue, float size);
	virtual void OnCollision(CollisonLayer layer, bool isEnter);
	virtual void OnDamage();
	virtual void OnDie();
	virtual void DelayDie(double dt);
	virtual void PlayAnimation(double dt);
	virtual void InitAnimation();
	virtual void InitTexture(const char* filename);
public:
	Weapon* _weapon;
	Animator* _animator;
	double _curHealth;
	double _maxHealth;
protected:
	void Move(double dt);
protected:
	Vec3 _moveDirection;
	double _moveSpeed;
	double _dieDelayTime = 0;
	bool _isDie = false;
};

#endif