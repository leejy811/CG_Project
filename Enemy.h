#ifndef __ENEMY_H__
#define __ENEMY_H__

#pragma once

#include "Character.h"

using namespace std;

class Enemy : public Character
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Render();
private:

};

#endif