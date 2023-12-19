#ifndef __SOUND_H__
#define __SOUND_H__

#pragma once

#include <windows.h>
#include <mmsystem.h>    
#pragma comment(lib,"winmm.lib")

#define BGM_S "sound/BGM.wav"
#define SHOOT_S "sound/ShootSFX.wav"
#define HIT_S "sound/HitSFX.wav"
#define WALK_S "sound/WalkSFX.wav"
#define DIE_S "sound/DieSFX.wav"
#define CLEAR_S "sound/ClearSFX.wav"

enum Sound
{
	BGM_E,
	SHOOT_E,
	HIT_E,
	WALK_E,
	DIE_E,
	CLEAR_E
};

using namespace std;

class SoundManager
{
public:

	static SoundManager* GetInstance()
	{
		if (_instance == NULL)
		{
			_instance = new SoundManager();
		}

		return _instance;
	}

	void PlaySoundToEnum(Sound sound);
private:
	SoundManager();
	SoundManager(const SoundManager& other);
	~SoundManager();

	static SoundManager* _instance;

	bool _isWalkSound = false;
};

#endif