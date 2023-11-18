#ifndef __FACE_H__
#define __FACE_H__

#pragma once
#include "Vertex.h"

using namespace std;

class Face
{
public:
	int				_index;
	Vec3	_normal;
	vector<Vertex*>	_vertices; // Triangle : num. vertex -> 3
public:
	Face() { }
	Face(int index, Vertex* v0, Vertex* v1, Vertex* v2)
	{
		_index = index;
		_vertices.push_back(v0);
		_vertices.push_back(v1);
		_vertices.push_back(v2);
	}
	~Face() { }
public:
	int		getIndex(Vertex* v)
	{
		for (int i = 0; i < 3; i++)
		{
			if (_vertices[i] == v)
			{
				return i;
			}
		}
		return -1;
	}
};

#endif
