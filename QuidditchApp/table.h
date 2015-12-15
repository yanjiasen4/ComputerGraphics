#pragma once
#ifndef __TABLE_H__
#define __TABLE_H__

#include <GL/GLUT.H>
#include "matrix.h"

const float t_length = 30;
const float t_width = 49;
const float t_thick = 0;

class Table
{
public:
	Table();
	~Table();
	void init();
	void render();
	void update();
private:
	Point3D pos;
	float length;
	float width;
	float thick;
};



#endif  __TABLE_H__