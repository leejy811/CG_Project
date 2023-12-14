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
	void DrawStringInfo();
	void DrawHealthBar(int width, int height);
private:
	Vec3 _mousePos;
};

#endif