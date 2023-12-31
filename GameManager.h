#ifndef __GAME_H__
#define __GAME_H__

#pragma once

#include "Camera.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "UIManager.h"
#include "MapTile.h"
#include <vector>

#define WIDTH 1280
#define HEIGHT 720
#define DELTA_TIME 0.02

using namespace std;

class GameManager
{
public:
	static GameManager* GetInstance()
	{
		if (_instance == NULL)
		{
			_instance = new GameManager();
		}
		return _instance;
	}
	void Init();
	void Update(double dt);
	void Render();
	void HandleKeyInput(unsigned char key, int state);
	void HandleSpecialInput(int  key, int state);
	void HandleMouseInput(int x, int y, int state, int clickState);

	Player* GetPlayer();
	int GetCurStage();
	int GetCurEnemyCount();
	bool GetIsStart();
	void SetCurEnemyCount();
	void ResetGame();
private:
	GameManager();
	GameManager(const GameManager& other);
	~GameManager();

	void SpawnEnemy(double dt);
	void DetectCollison();
	void DrawMinimap();
	void InitStage();
	void CheckStage();
	void UpdateStage();
private:
	static GameManager* _instance;

	Camera* _mainCamera;
	UIManager* _uiManager;
	Player* _player;
	vector<Enemy*> _enemies;
	vector<MapTile*> _mapTiles;

	//Enemy
	int _curEnemyCount = 0;
	int _enemyPoolSize = 3;
	int _enemySpawnCool = 200;
	int _curEnemySpawnTime;

	//Stage
	int _curStage = 1;

	bool _isStart = false;
};

#endif