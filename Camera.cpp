#include "Camera.h"
#include "GL/glut.h"

Camera::Camera()
{
	_up.set(0, 1, 0);
}

Camera::Camera(Vec3 os, Object& tar)
	: offset(os), _target(&tar)
{
	_up.set(0, 1, 0);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	_front = _target->position;
	_position = _target->position + offset;
}

void Camera::Render()
{
	SetViewMatrix(_position, _up, _front);
}

void Camera::SetViewMatrix(Vec3& pos, Vec3& up, Vec3& front)
{
	gluLookAt(pos.x(), pos.y(), pos.z(), front.x(), front.y(), front.z(), up.x(), up.y(), up.z());
}

void Camera::SetTarget(Object& tar)
{
	_target = &tar;
}