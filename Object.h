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
	~Object();

	virtual void Init();
	virtual void Update();
	virtual void Render();
public:
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;
private:
	void LoadObject(char* filename);
	void ComputeNormal();
	void SetNeighbor();
private:
	vector<Vertex*> _vertices;
	vector<Face*> _faces;
};

#endif