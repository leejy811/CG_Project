#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#pragma once

#include "Object.h"

using namespace std;

class Character : public Object
{
public:
	Character();
	~Character();

	virtual void Init();
	virtual void Update();
	virtual void Render();
private:

};

#endif