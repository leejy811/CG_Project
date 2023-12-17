#include "AnimationState.h"

AnimationState::AnimationState()
{

}

AnimationState::AnimationState(State s, double speed, bool isLoop)
{
	state = s;
	_speed = speed;
	_isLoop = isLoop;
	_curFrame = 0;

	switch (s)
	{
	case IDLE:
		frames.push_back(new Frame(PLAYER_IDLE1, 1));
		frames.push_back(new Frame(PLAYER_IDLE2, 1));
		break;
	case MOVE:
		frames.push_back(new Frame(ROBOT, 1));
		frames.push_back(new Frame(ROBOT1, 1));
		frames.push_back(new Frame(ROBOT2, 1));
		break;
	case DIE:
		frames.push_back(new Frame(ROBOT, 1));
		frames.push_back(new Frame(ROBOT1, 1));
		frames.push_back(new Frame(ROBOT2, 1));
		break;
	default:
		break;
	}
}

AnimationState::~AnimationState()
{

}