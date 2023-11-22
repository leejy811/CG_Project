#ifndef __PLAYER_H__
#define __PLAYER_H__

#pragma once

#include "Character.h"

#define KEY_DOWN 0
#define KEY_UP 1
#define MOUSE_MOTION 0
#define MOUSE_CLICK 1

using namespace std;

class Player : public Character
{
public:
	Player();
	Player(const char* filename);
	Player(const char* filename, Vec3 pos, Vec3 ro, Vec3 s);
	~Player();

	void Init();
	void Update();
	void Render();
	void HandleInput(unsigned char key, int state);
	void HandleSpecialInput(int  key, int state);
	void HandleMouseInput(int x, int y, int state);
private:

};

#endif