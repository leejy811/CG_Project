#include "GameManager.h"
#include "SoundManager.h"
#include "GL/freeglut.h"
#include <stdlib.h>
#include <time.h>

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager()
{

}

GameManager::GameManager(const GameManager& other)
{

}

GameManager::~GameManager()
{

}

void GameManager::Init()
{
	srand(time(NULL));

	_player = new Player("img/PlayerTexture.bmp", Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(1, 1, 1), 0.5, 10, 2);
	_mainCamera = new Camera(Vec3(0, 10, 2), *_player);
	_uiManager = new UIManager();

	for (int i = 0; i < _enemyPoolSize; i++)
	{
		_enemies.push_back(new Enemy("img/EnemyTexture.bmp", Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(1, 1, 1), *_player, 0.5, 1, 0.5));
	}

	_mapTiles.push_back(new MapTile(50, *_player, Vec3(1, 0, 1)));
	_mapTiles.push_back(new MapTile(50, *_player, Vec3(1, 0, -1)));
	_mapTiles.push_back(new MapTile(50, *_player, Vec3(-1, 0, 1)));
	_mapTiles.push_back(new MapTile(50, *_player, Vec3(-1, 0, -1)));

	InitStage();

	_isStart = false;

	SoundManager::GetInstance()->PlaySoundToEnum(BGM_E);
}

void GameManager::Update(double dt)
{
	CheckStage();
	SpawnEnemy(dt);
	DetectCollison();
	_player->Update(dt);
	_mainCamera->Update();

	for (auto e : _enemies)
	{
		e->Update(dt);
	}

	for (auto m : _mapTiles)
	{
		m->Update();
	}
}

void GameManager::Render()
{
	DrawMinimap();

	glViewport(0, 0, WIDTH, HEIGHT);
	glLoadIdentity();
	_mainCamera->SetViewMatrix();
	_uiManager->Render();
	_player->Render();

	for (auto e : _enemies)
	{
		e->Render();
	}

	for (auto m : _mapTiles)
	{
		m->Render();
	}
}

void GameManager::HandleKeyInput(unsigned char key, int state)
{ 
	if (!_isStart && state == KEY_DOWN)
		_isStart = true;
	_player->HandleInput(key, state);
}

void GameManager::HandleSpecialInput(int  key, int state)
{
	if (!_isStart && state == KEY_DOWN)
		_isStart = true;
	_player->HandleSpecialInput(key, state);
}

void GameManager::HandleMouseInput(int x, int y, int state, int clickState)
{
	if (!_isStart && state != MOUSE_MOTION)
		_isStart = true;
	_uiManager->SetMousePositon(x, y);
	_player->HandleMouseInput(x, y, state, clickState);
}

Player* GameManager::GetPlayer()
{
	return _player;
}

int GameManager::GetCurStage()
{
	return _curStage;
}

int GameManager::GetCurEnemyCount()
{
	return _curEnemyCount;
}

bool GameManager::GetIsStart()
{
	return _isStart;
}

void GameManager::SetCurEnemyCount()
{
	_curEnemyCount--;
}

void GameManager::SpawnEnemy(double dt)
{
	if (!_isStart) return;
	int time = glutGet(GLUT_ELAPSED_TIME);

	if (time - _curEnemySpawnTime > _enemySpawnCool * (1.0 / dt) * DELTA_TIME)
	{
		for (auto e : _enemies)
		{
			if (!e->isActive)
			{
				_curEnemySpawnTime = time;
				e->isActive = true;
				double angle = (double)(rand() % 360) * (3.14152 / 180);
				e->position = Vec3(6 * cos(angle), 0, 6 * sin(angle));
				e->_animator->ChangeState(MOVE);
				break;
			}
		}
	}
}

void GameManager::DetectCollison()
{
	//Bullet Collision
	for (auto e : _enemies)
	{
		if (!e->isActive) continue;

		//Enemy - Bullet
		for (auto b : _player->_weapon->_bullets)
		{
			if (!b->isActive) continue;
			double distance = (e->position - b->position).getNorm();
			if (distance < e->collisionRad + b->collisionRad)
			{
				e->OnCollision(BULLET, true);
				b->OnCollision(CHARACTER, true);
			}
		}

		//Player - Bullet
		for (auto b : e->_weapon->_bullets)
		{
			if (!b->isActive) continue;
			double distance = (_player->position - b->position).getNorm();
			if (distance < _player->collisionRad + b->collisionRad)
			{
				_player->OnCollision(BULLET, true);
				b->OnCollision(CHARACTER, true);
			}
		}
	}

	//Character Collision
	for (auto e : _enemies)
	{
		if (!e->isActive) continue;
		double distance = (e->position - _player->position).getNorm();
		if (distance < e->collisionRad + _player->collisionRad)
		{
			e->OnCollision(CHARACTER, true);
		}
		else
		{
			e->OnCollision(CHARACTER, false);
		}
	}
}

void GameManager::DrawMinimap()
{
	glViewport(WIDTH * (55.0 / 64.0), HEIGHT * (3.0 / 4.0), WIDTH * (9.0 / 64.0), HEIGHT / 4);

	glLoadIdentity();
	_mainCamera->SetViewMatrix();

	_player->MinimapRender(1, 0, 0, 0.3);

	for (auto e : _enemies)
	{
		if (!e->isActive) continue;
		e->MinimapRender(0, 1, 0, 0.2);
	}

	glFlush();
}

void GameManager::InitStage()
{
	_curStage = 1;
	_curEnemyCount = 5;
}

void GameManager::CheckStage()
{
	if (_curEnemyCount <= 0)
		UpdateStage();
}

void GameManager::UpdateStage()
{
	SoundManager::GetInstance()->PlaySoundToEnum(CLEAR_E);
	_curStage++;
	_curEnemyCount = 5 + _curStage * 2;
}

void GameManager::ResetGame()
{
	delete _mainCamera;
	delete _uiManager;

	_enemies.clear();
	_mapTiles.clear();

	Init();
}