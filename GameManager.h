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
	void HandleInput(unsigned char key);
	void HandleSpecialInput(int  key);
private:
	Camera* _mainCamera;
	Player* _player;
	vector<Enemy*> _enemies;
	vector<Bullet*> _bullets;
};

#endif