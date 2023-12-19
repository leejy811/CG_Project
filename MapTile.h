#ifndef __MAPTILE_H__
#define __MAPTILE_H__

#pragma once

#include "Vec3.h"
#include "Player.h"
#include "GL/freeglut.h"

using namespace std;

class MapTile
{
public:
	MapTile();
	MapTile(double size, Player& player, Vec3 pos);
	~MapTile();

	void Update();
	void Render();
private:
	void CheckPlayer();
private:
	Vec3 _position;
	Player* _player;
	double _mapSize;
};

#endif