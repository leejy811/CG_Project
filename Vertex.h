#ifndef __VERTEX_H__
#define __VERTEX_H__

#pragma once

#include "Vec3.h"
#include "Face.h"
#include <vector>

using namespace std;

class Vertex
{
public:
	int				_index;
	Vec3	_pos; // X,Y,Z
	Vec3	_normal;
	vector<Face*>	_nbFaces; // Neighbor face
	vector<Vertex*>	_nbVertices; // Neighbor vertex
public:
	Vertex() { }
	Vertex(int index, Vec3 pos, Vec3 vel, double invMass)
	{
		_index = index;
		_pos = pos;
	}
	~Vertex() { }
public:
	inline double x(void) { return _pos.x(); }
	inline double y(void) { return _pos.y(); }
	inline double z(void) { return _pos.z(); }
public:
	bool	hasNbVertex(Vertex* v) 
	{
		for (auto nv : _nbVertices)
		{
			if (nv == v)
			{
				return true;
			}
		}
		return false;
	}
};

#endif