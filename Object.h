#ifndef __OBJECT_H__
#define __OBJECT_H__

#pragma once

#include "Vec3.h"

class Object
{
public:
	Object();
	~Object();

	virtual void Init();
	virtual void Update();
	virtual void Render();

public:
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;
private:
	
};

#endif