#ifndef __OBJECT_H__
#define __OBJECT_H__

#pragma once

#include <vector>
#include "Vec3.h"
#include "Vertex.h"
#include "Face.h"

using namespace std;

enum CollisonLayer
{
	PLAYER,
	ENEMY,
	BULLET
};

class Object
{
public:
	Object();
	Object(const char* filename);
	Object(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, double rad);
	~Object();

	virtual void Update();
	virtual void Render();
	virtual void OnCollision(CollisonLayer layer);
public:
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;
	double collisionRad;
	bool isActive = true;
protected:
	void LoadObject(const char* filename);
	void ComputeNormal();
	void ThisRender();
	void SetTransform();
protected:
	vector<Face*> _faces;
	vector<Object*> _childObjects;
};

#endif