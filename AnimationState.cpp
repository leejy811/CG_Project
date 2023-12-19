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
		frames.push_back(new Frame(PLAYER_IDLE1, 0.5));
		frames.push_back(new Frame(PLAYER_IDLE2, 0.5));
		break;
	case MOVE:
		frames.push_back(new Frame(PLAYER_MOVE1, 1.5));
		frames.push_back(new Frame(PLAYER_MOVE2, 1.1));
		frames.push_back(new Frame(PLAYER_MOVE3, 1.1));
		frames.push_back(new Frame(PLAYER_MOVE4, 0.9));
		break;
	case DIE:
		frames.push_back(new Frame(PLAYER_IDLE1, 0.5));
		frames.push_back(new Frame(PLAYER_DIE, 0));
		break;
	default:
		break;
	}
}

AnimationState::~AnimationState()
{
	frames.clear();
}