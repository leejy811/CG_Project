#include "Object.h"
#include "gl\glut.h"
#include <Windows.h>

#pragma warning(disable : 4996)

Object::Object()
{

}

Object::~Object()
{

}

void Object::Init()
{

}

void Object::Update()
{

}

void Object::Render()
{
	for (auto f : _faces)
	{
		glBegin(GL_POLYGON);
		glNormal3f(f->_normal.x(), f->_normal.y(), f->_normal.z());
		for (int j = 0; j < 3; j++)
		{
			glVertex3f(f->_vertices[j]->x(), f->_vertices[j]->y(), f->_vertices[j]->z());
		}
		glEnd();
	}
}

void Object::LoadObject(char* filename)
{
	FILE* fp;
	char header[256] = { 0 };
	double pos[3];
	int v_index[3];
	int index = 0;

	fopen_s(&fp, filename, "r");
	while (fscanf(fp, "%s %lf %lf %lf", header, &pos[0], &pos[1], &pos[2]) != EOF)
	{
		if (header[0] == 'v' && header[1] == NULL)
		{
			_vertices.push_back(new Vertex(index++, Vec3(pos[0], pos[1], pos[2])));
		}
	}

	index = 0;
	fseek(fp, 0, SEEK_SET);
	while (fscanf(fp, "%s %d %d %d", header, &v_index[0], &v_index[1], &v_index[2]) != EOF)
	{
		if (header[0] == 'f' && header[1] == NULL)
		{
			auto v0 = _vertices[v_index[0] - 1];
			auto v1 = _vertices[v_index[1] - 1];
			auto v2 = _vertices[v_index[2] - 1];
			_faces.push_back(new Face(index++, v0, v1, v2));
		}
	}
	fclose(fp);

	ComputeNormal();
	SetNeighbor();
}

void Object::ComputeNormal()
{
	for (auto f : _faces)
	{
		auto v0 = f->_vertices[0]->_pos;
		auto v1 = f->_vertices[1]->_pos;
		auto v2 = f->_vertices[2]->_pos;
		auto normal = (v0 - v1).cross(v0 - v2);
		normal.normalize();
		f->_normal = normal;
	}

	for (auto v : _vertices)
	{
		v->_normal.clear();
		for (auto nf : v->_nbFaces)
		{
			v->_normal += nf->_normal;
		}
		v->_normal /= v->_nbFaces.size();
	}
}

void Object::SetNeighbor()
{
	for (auto v : _vertices)
	{
		v->_nbVertices.clear();
	}

	for (auto f : _faces)
	{
		for (int j = 0; j < 3; j++)
		{
			f->_vertices[j]->_nbFaces.push_back(f);
		}
	}
}