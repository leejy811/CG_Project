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
	SetViewMatrix();
}

void Camera::SetViewMatrix()
{
	gluLookAt(_position.x(), _position.y(), _position.z(), _front.x(), _front.y(), _front.z(), _up.x(), _up.y(), _up.z());
}

void Camera::SetTarget(Object& tar)
{
	_target = &tar;
}