#ifndef __UI_H__
#define __UI_H__

#pragma once

#pragma warning(disable : 4996)

#include "Vec3.h"

using namespace std;

class UIManager
{
public:
	UIManager();
	~UIManager();

	void Render();
	void SetMousePositon(int x, int y);
private:
	void DrawMouse(int mouseSize);
	void DrawString(const char* str, int value, float x, float y);
	void DrawInfo();
	void DrawHealthBar(int width, int height);
	void DrawStart();
private:
	Vec3 _mousePos;
};

#endif