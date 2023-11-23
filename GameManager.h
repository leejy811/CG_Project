#ifndef __GAME_H__
#define __GAME_H__

#pragma once

#include "Camera.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "UIManager.h"
#include <vector>

#define WIDTH 1600
#define HEIGHT 900

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
	void HandleMouseInput(int x, int y, int state, int clickState);
private:
	Camera* _mainCamera;
	Player* _player;
	vector<Enemy*> _enemies;
	UIManager* _uiManager;
};

#endif