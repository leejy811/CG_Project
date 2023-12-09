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
#define DELTA_TIME 0.2

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
	void SpawnEnemy();
	void DetectCollison();
private:
	Camera* _mainCamera;
	UIManager* _uiManager;
	Player* _player;
	vector<Enemy*> _enemies;

	//Enemy
	int _curEnemyIndex = 0;
	int _enemyPoolSize = 10;
	int _enemySpawnCool = 3000;
	int _curEnemySpawnTime;
};

#endif