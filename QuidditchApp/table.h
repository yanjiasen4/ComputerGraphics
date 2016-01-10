#pragma once
#ifndef __TABLE_H__
#define __TABLE_H__

#include "glhf.h"
#include "matrix.h"
#include "terrain.h"

const float t_length = 15;
const float t_width = 25;
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
	Terrain *terrain;
	Point3D pos;
	float length;
	float width;
	float thick;
};



#endif  __TABLE_H__