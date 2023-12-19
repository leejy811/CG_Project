#ifndef __FACE_H__
#define __FACE_H__

#pragma once
#include "Vec3.h"
#include <vector>

using namespace std;

class Face
{
public:
	int				_index;
	Vec3	_normal;
	vector<Vec3>	_vertices;
	vector<Vec3>	_uvs;
	vector<Vec3>	_vertNormals;
public:
	Face() { }
	Face(int index, Vec3 v0, Vec3 v1, Vec3 v2, Vec3 u0, Vec3 u1, Vec3 u2, Vec3 n0, Vec3 n1, Vec3 n2)
	{
		_index = index;
		_vertices.push_back(v0);
		_vertices.push_back(v1);
		_vertices.push_back(v2);

		_uvs.push_back(u0);
		_uvs.push_back(u1);
		_uvs.push_back(u2);

		_vertNormals.push_back(n0);
		_vertNormals.push_back(n1);
		_vertNormals.push_back(n2);
	}
	~Face()
	{
		_vertices.clear();
		_uvs.clear();
		_vertNormals.clear();
	}
};

#endif
