#include "SoundManager.h"
#include <stdio.h>

SoundManager* SoundManager::_instance = nullptr;

SoundManager::SoundManager()
{

}

SoundManager::SoundManager(const SoundManager& other)
{

}

SoundManager::~SoundManager()
{

}

void SoundManager::PlaySoundToEnum(Sound sound)
{
	switch (sound)
	{
	case BGM_E:
		PlaySound(TEXT(BGM_S), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		_isWalkSound = false;
		break;
	case SHOOT_E:
		PlaySound(TEXT(SHOOT_S), NULL, SND_FILENAME | SND_ASYNC);
		_isWalkSound = false;
		break;
	case HIT_E:
		PlaySound(TEXT(HIT_S), NULL, SND_FILENAME | SND_ASYNC);
		_isWalkSound = false;
		break;
	case WALK_E:
		if (!_isWalkSound)
		{
			PlaySound(TEXT(WALK_S), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			_isWalkSound = true;
		}
		break;
	case DIE_E:
		PlaySound(TEXT(DIE_S), NULL, SND_FILENAME | SND_ASYNC);
		_isWalkSound = false;
		break;
	case CLEAR_E:
		PlaySound(TEXT(CLEAR_S), NULL, SND_FILENAME | SND_ASYNC);
		_isWalkSound = false;
		break;
	default:
		break;
	}
}