#ifndef __ANIMATOR_H__
#define __ANIMATOR_H__

#pragma once

using namespace std;

#include "AnimationState.h"
#include <vector>

class Animator
{
public:
	Animator();
	Animator(State initialState);
	~Animator();

	void ChangeState(State state);
public:
	State _curState;
	vector<AnimationState*> _states;
	double _lerpAlpha;
};

#endif