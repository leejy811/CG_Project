#include "Frame.h"

#pragma warning(disable : 4996)

Frame::Frame()
{

}

Frame::Frame(const char* filename, double time)
{
	LoadObject(filename);
	_duration = time;
}

Frame::~Frame()
{
	_faces.clear();
}

void Frame::LoadObject(const char* filename)
{
	FILE* fp;
	char header[256] = { 0 };
	double pos[3];
	double uv[3];
	double normal[3];
	int v_index[3];
	int u_index[3];
	int n_index[3];
	int index = 0;

	vector<Vec3> vertices;
	vector<Vec3> uvs;
	vector<Vec3> normals;

	fopen_s(&fp, filename, "r");
	while (1)
	{
		if (fscanf(fp, "%s", header) == EOF) break;

		if (strcmp(header, "v") == 0)
		{
			fscanf(fp, "%lf %lf %lf", &pos[0], &pos[1], &pos[2]);
			vertices.push_back(Vec3(pos[0], pos[1], pos[2]));
		}
		else if (strcmp(header, "vt") == 0)
		{
			fscanf(fp, "%lf %lf", &uv[0], &uv[1]);
			uvs.push_back(Vec3(uv[0], uv[1], 0.0));
		}
		else if (strcmp(header, "vn") == 0)
		{
			fscanf(fp, "%lf %lf %lf", &normal[0], &normal[1], &normal[2]);
			normals.push_back(Vec3(normal[0], normal[1], normal[2]));
		}
		else if (strcmp(header, "f") == 0)
		{
			fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d ", &v_index[0], &u_index[0], &n_index[0], &v_index[1], &u_index[1], &n_index[1], &v_index[2], &u_index[2], &n_index[2]);
			auto v0 = vertices[v_index[0] - 1];
			auto v1 = vertices[v_index[1] - 1];
			auto v2 = vertices[v_index[2] - 1];
			auto u0 = uvs[u_index[0] - 1];
			auto u1 = uvs[u_index[1] - 1];
			auto u2 = uvs[u_index[2] - 1];
			auto n0 = normals[n_index[0] - 1];
			auto n1 = normals[n_index[1] - 1];
			auto n2 = normals[n_index[2] - 1];
			_faces.push_back(new Face(index++, v0, v1, v2, u0, u1, u2, n0, n1, n2));
		}
	}
	fclose(fp);
}