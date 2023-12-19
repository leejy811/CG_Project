#include "MapTile.h"
#include "GL/freeglut.h"
#include "bmpfuncs.h"

MapTile::MapTile()
{

}

MapTile::MapTile(double size, Player& player, Vec3 pos)
{
	_mapSize = size;
	_player = &player;
	_position = pos * (size / 2);
}

MapTile::~MapTile()
{

}

void MapTile::Update()
{
	CheckPlayer();
}

void MapTile::Render()
{
	glPushMatrix();

	glTranslatef(_position.x(), 0, _position.z());
	glBegin(GL_QUADS);
	glVertex3f(-_mapSize, 0.0f, -_mapSize);
	glVertex3f(-_mapSize, 0.0f, _mapSize);
	glVertex3f(_mapSize, 0.0f, _mapSize);
	glVertex3f(_mapSize, 0.0f, -_mapSize);
	glEnd();

	glPopMatrix();
}

void MapTile::CheckPlayer()
{
	double diffX = _player->position.x() - _position.x();
	double diffZ = _player->position.z() - _position.z();

	if (diffX > _mapSize)
		_position += Vec3(_mapSize * 2, 0, 0);
	else if (diffX < -_mapSize)
		_position -= Vec3(_mapSize * 2, 0, 0);

	if (diffZ > _mapSize)
		_position += Vec3(0, 0, _mapSize * 2);
	else if (diffZ < -_mapSize)
		_position -= Vec3(0, 0, _mapSize * 2);
}