#pragma once
#ifndef __STRINGDRAW_H__
#define __STRINGDRAW_H__

#include "glhf.h"
#include <windows.h>
#include <stdlib.h>

#define MAX_CHAR 128

using namespace std;

const int FPS_X = 0;
const int FPS_Y = 0;

class StringDraw
{
public:
	StringDraw();
	StringDraw(string c);
	~StringDraw();

	void init();
	void render();
	void update(string c);

	void setContent(string c);
private:
	int x, y;
	string content;
	GLuint lists;
};

#endif