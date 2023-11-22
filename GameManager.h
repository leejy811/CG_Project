#ifndef __GAME_H__
#define __GAME_H__

#pragma once

#include "Camera.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include <vector>

using namespace std;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Init();
	void Update();
	void Render();
	void HandleKeyInput(unsigned char key, int state);
	void HandleSpecialInput(int  key, int state);
	void HandleMouseInput(int x, int y, int state);
private:
	Camera* _mainCamera;
	Player* _player;
	vector<Enemy*> _enemies;
	vector<Bullet*> _bullets;
};

#endif