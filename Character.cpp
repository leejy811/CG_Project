#include "Character.h"

Character::Character()
{
	
}

Character::Character(const char* filename)
{
	LoadObject(filename);
	position = Vec3(0, 0, 0);
	rotation = Vec3(0, 0, 0);
	scale = Vec3(1, 1, 1);
}

Character::Character(const char* filename, Vec3 pos, Vec3 ro, Vec3 s)
{
	LoadObject(filename);
	position = pos;
	rotation = ro;
	scale = s;
}

Character::~Character()
{

}

void Character::Init()
{

}

void Character::Update()
{

}

void Character::Render()
{
	Object::Render();
}

void Character::Move()
{
	Translate(_moveDirection);
}