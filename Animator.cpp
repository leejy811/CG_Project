#include "Animator.h"

Animator::Animator()
{

}

Animator::Animator(State initialState)
{
	_curState = initialState;

	_states.push_back(new AnimationState(IDLE, 2, true));
	_states.push_back(new AnimationState(MOVE, 1, true));
	_states.push_back(new AnimationState(DIE, 1, false));
}

Animator::~Animator()
{
	_states.clear();
}

void Animator::ChangeState(State state)
{
	_curState = state;
}