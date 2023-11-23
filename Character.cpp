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

	_weapon = new Weapon();
}

Character::Character(const char* filename, Vec3 pos, Vec3 ro, Vec3 s)
{
	LoadObject(filename);
	position = pos;
	rotation = ro;
	scale = s;

	_weapon = new Weapon();
}

Character::~Character()
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