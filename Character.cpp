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

Character::Character(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, double rad, double h)
{
	LoadObject(filename);
	position = pos;
	rotation = ro;
	scale = s;
	collisionRad = rad;
	_health = h;

	_weapon = new Weapon();
}

Character::~Character()
{

}

void Character::Update()
{
	Move();
	_weapon->Update();
}

void Character::Render()
{
	Object::Render();

	for (auto b : _weapon->_bullets)
	{
		b->Render();
	}
}

void Character::OnCollision(CollisonLayer layer)
{
	if (layer == BULLET)
		OnDamage();
}

void Character::Move()
{
	position += _moveDirection;
}

void Character::OnDamage()
{
	_health -= 1;

	if (_health <= 0)
	{
		isActive = false;
	}
}