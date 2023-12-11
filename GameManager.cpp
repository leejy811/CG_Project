#include "GameManager.h"
#include "GL/freeglut.h"
#include <stdlib.h>
#include <time.h>

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

void GameManager::Init()
{
	srand(time(NULL));

	_player = new Player("OBJ/Soldier.obj", Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(0.5, 0.5, 0.5), 20, 1000, 3);
	_mainCamera = new Camera(Vec3(0, 500, 100), *_player);
	_uiManager = new UIManager();

	for (int i = 0; i < _enemyPoolSize; i++)
	{
		_enemies.push_back(new Enemy("OBJ/Soldier.obj", Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(0.5, 0.5, 0.5), *_player, 20, 1, 1));
	}
}

void GameManager::Update(double dt)
{
	SpawnEnemy(dt);
	DetectCollison();
	_player->Update(dt);
	_mainCamera->Update();

	for (auto e : _enemies)
	{
		e->Update(dt);
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
}

void GameManager::HandleKeyInput(unsigned char key, int state)
{
	_player->HandleInput(key, state);
}

void GameManager::HandleSpecialInput(int  key, int state)
{
	_player->HandleSpecialInput(key, state);
}

void GameManager::HandleMouseInput(int x, int y, int state, int clickState)
{
	_uiManager->SetMousePositon(x, y);
	_player->HandleMouseInput(x, y, state, clickState);
}

void GameManager::SpawnEnemy(double dt)
{
	int time = glutGet(GLUT_ELAPSED_TIME);

	if (time - _curEnemySpawnTime > _enemySpawnCool * (1.0 / dt))
	{
		if (_curEnemyIndex == _enemyPoolSize) return;
		_curEnemySpawnTime = time;
		_enemies[_curEnemyIndex]->isActive = true;

		double angle = (double)(rand() % 360) * (3.14152 / 180);
		_enemies[_curEnemyIndex]->position = Vec3(100 * cos(angle), 0, 100 * sin(angle));

		_curEnemyIndex++;
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
	glViewport(WIDTH * (55.0 / 64.0), HEIGHT * (3.0 / 4.0), WIDTH * (9.0 / 64.0), HEIGHT / 5);

	glLoadIdentity();
	_mainCamera->SetViewMatrix();

	_player->MinimapRender(0, 1, 0, 30);

	for (auto e : _enemies)
	{
		e->MinimapRender(1, 0, 0, 20);
	}

	glFlush();
}