#include "Player.h"
#include "GL/freeglut.h"

Player::Player()
{
	
}

Player::Player(const char* filename)
{
    LoadObject(filename);
    position = Vec3(0, 0, 0);
    rotation = Vec3(0, 0, 0);
    scale = Vec3(1, 1, 1);
}

Player::Player(const char* filename, Vec3 pos, Vec3 ro, Vec3 s)
{
    LoadObject(filename);
    position = pos;
    rotation = ro;
    scale = s;
}

Player::~Player()
{
	
}

void Player::Init()
{

}

void Player::Update()
{
    Move();
}

void Player::Render()
{
	Character::Render();
}

void Player::HandleInput(unsigned char key, int state)
{
    if (state == KEY_DOWN)     //Down
    {
        
    }
    else if (state == KEY_UP)    //Up
    {

    }
}

void Player::HandleSpecialInput(int  key, int state)
{
    if (state == KEY_DOWN)     //Down
    {
        printf("%d Key Down\n", key);
        switch (key)
        {
        case GLUT_KEY_LEFT:
            if ((_moveDirection + Vec3(-1, 0, 0)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(-1, 0, 0);
            break;
        case GLUT_KEY_RIGHT:
            if ((_moveDirection + Vec3(1, 0, 0)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(1, 0, 0);
            break;
        case GLUT_KEY_DOWN:
            if ((_moveDirection + Vec3(0, 0, 1)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(0, 0, 1);
            break;
        case GLUT_KEY_UP:
            if ((_moveDirection + Vec3(0, 0, -1)).getNorm() <= _moveSpeed)
                _moveDirection += Vec3(0, 0, -1);
            break;
        }
    }
    else if (state == KEY_UP)    //Up
    {
        printf("%d Key Up\n", key);
        switch (key)
        {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            _moveDirection = Vec3(0, 0, _moveDirection.z());
            break;
        case GLUT_KEY_DOWN:
        case GLUT_KEY_UP:
            _moveDirection = Vec3(_moveDirection.x(), 0, 0);
            break;
        }
    }
    glutPostRedisplay();
}

void Player::HandleMouseInput(int x, int y, int state)
{
    if (state == MOUSE_MOTION)
    {
        rotation = Vec3(0, (atan2(y, x) / 3.141592) * 180 - 90, 0);
    }
    else if (state == MOUSE_CLICK)
    {

    }
}