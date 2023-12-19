#ifndef __FRAME_H__
#define __FRAME_H__

#pragma once

using namespace std;

#include "Face.h"
#include <vector>

#define PLAYER_IDLE1 "OBJ/Player_Idle1.obj"
#define PLAYER_IDLE2 "OBJ/Player_Idle2.obj"
#define PLAYER_MOVE1 "OBJ/Player_Move1.obj"
#define PLAYER_MOVE2 "OBJ/Player_Move2.obj"
#define PLAYER_MOVE3 "OBJ/Player_Move3.obj"
#define PLAYER_MOVE4 "OBJ/Player_Move4.obj"
#define PLAYER_DIE "OBJ/Player_Die.obj"

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