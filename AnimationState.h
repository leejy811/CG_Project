#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#pragma once

using namespace std;

#include "Frame.h"
#include <vector>

enum State
{
	IDLE,
	MOVE,
	DIE
};

class AnimationState
{
public:
	AnimationState();
	AnimationState(State s, double speed, bool isLoop);
	~AnimationState();

public:
	vector<Frame*> frames;
	State state;
	int _curFrame;
	double _speed;
	bool _isLoop;
};

#endif