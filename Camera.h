#ifndef __CAMERA_H__
#define __CAMERA_H__

#pragma once

#include "Vec3.h"
#include "Object.h"

class Camera
{
public:
	Camera();
	~Camera();

	void SetViewMatrix(Vec3& pos, Vec3& up, Vec3& front);
	void SetTarget(Object& tar);
public:
	Vec3 position;
	Vec3 up;
	Vec3 front;
	Object target;
private:

};

#endif