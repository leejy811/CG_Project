#ifndef __OBJECT_H__
#define __OBJECT_H__

#pragma once

#include <vector>
#include "Vec3.h"
#include "Vertex.h"
#include "Face.h"

using namespace std;

class Object
{
public:
	Object();
	Object(const char* filename);
	Object(const char* filename, Vec3 pos, Vec3 ro, Vec3 s);
	~Object();

	virtual void Update();
	virtual void Render();
public:
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;
protected:
	void LoadObject(const char* filename);
	void ComputeNormal();
	void SetTransform();
	void Translate(Vec3 trans);
protected:
	vector<Face*> _faces;
};

#endif