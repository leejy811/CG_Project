#ifndef __BULLET_H__
#define __BULLET_H__

#pragma once

#include "Object.h"

using namespace std;

class Bullet : public Object
{
public:
	Bullet();
	~Bullet();

	void Init();
	void Update();
	void Render();
private:

};

#endif