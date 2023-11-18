#ifndef __PLAYER_H__
#define __PLAYER_H__

#pragma once

#include "Character.h"

using namespace std;

class Player : public Character
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Render();
	void HandleInput(unsigned char key);
	void HandleSpecialInput(int  key);
private:

};

#endif