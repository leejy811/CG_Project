#include "GameManager.h"

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

void GameManager::Init()
{
	_player = new Player();
	_mainCamera = new Camera(Vec3(10, 10, 0), *_player);
}

void GameManager::Update()
{
	_player->Update();
	_mainCamera->Update();

	for (auto e : _enemies)
	{
		e->Update();
	}

	for (auto b : _bullets)
	{
		b->Update();
	}
}

void GameManager::Render()
{
	_mainCamera->Render();
	_player->Render();

	for (auto e : _enemies)
	{
		e->Render();
	}

	for (auto b : _bullets)
	{
		b->Render();
	}
}

void GameManager::HandleInput(unsigned char key)
{
	_player->HandleInput(key);
}

void GameManager::HandleSpecialInput(int  key)
{
	_player->HandleSpecialInput(key);
}