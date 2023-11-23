#include "GameManager.h"

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

void GameManager::Init()
{
	_player = new Player("OBJ/Soldier.obj", Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(0.5, 0.5, 0.5));
	_mainCamera = new Camera(Vec3(0, 500, 100), *_player);
	_uiManager = new UIManager();
}

void GameManager::Update()
{
	_player->Update();
	_mainCamera->Update();

	for (auto e : _enemies)
	{
		e->Update();
	}
}

void GameManager::Render()
{
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