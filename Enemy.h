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
	Enemy(const char* filename, Vec3 pos, Vec3 ro, Vec3 s);
	~Enemy();

	void Update();
	void Render();
private:

};

#endif