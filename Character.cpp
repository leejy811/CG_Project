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

Character::Character(const char* filename, Vec3 pos, Vec3 ro, Vec3 s, double rad, double h, double ms)
{
	LoadObject(filename);
	Init(pos, ro, s, rad, h, ms);

	_weapon = new Weapon();
	_childObjects.push_back(_weapon);
}

Character::~Character()
{

}

void Character::Init(Vec3 pos, Vec3 ro, Vec3 s, double rad, double h, double ms) {
	Object::Init(pos, ro, s, rad);
	_moveSpeed = ms;
	_health = h;
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

void Character::OnCollision(CollisonLayer layer, bool isEnter)
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