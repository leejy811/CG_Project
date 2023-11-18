#ifndef __PLAYER_H__
#define __PLAYER_H__

#pragma once

#include "Character.h"

class Player : public Character
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Render();
private:

};

#endif