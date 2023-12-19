#ifndef __CAMERA_H__
#define __CAMERA_H__

#pragma once

#include "Vec3.h"
#include "Object.h"

using namespace std;

class Camera
{
public:
	Camera();
	Camera(Vec3 off, Object& tar);
	~Camera();
	void Update();
	void Render();

	void SetViewMatrix();
	void SetTarget(Object& tar);

	Vec3 offset;
private:
	Vec3 _position;
	Vec3 _up;
	Vec3 _front;
	Object* _target;
};

#endif