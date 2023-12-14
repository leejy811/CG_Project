#ifndef __FRAME_H__
#define __FRAME_H__

#pragma once

using namespace std;

#include "Face.h"
#include <vector>

#define ROBOT "OBJ/Robot.obj"
#define ROBOT1 "OBJ/Robot1.obj"
#define ROBOT2 "OBJ/Robot2.obj"
#define PLAYER_IDLE "OBJ/Player_Idle.obj"
#define PLAYER_MOVE "OBJ/Player_Move.obj"
#define PLAYER_DIE "OBJ/Player_Die.obj"

#define ENEMY_IDLE "OBJ/Enemy_Idle.obj"
#define ENEMY_MOVE "OBJ/Enemy_Move.obj"
#define ENEMY_DIE "OBJ/Enemy_Die.obj"

class Frame
{
public:
	Frame();
	Frame(const char* filename, double time);
	~Frame();
public:
	vector<Face*> _faces;
	double _duration;
private:
	void LoadObject(const char* filename);
};

#endif