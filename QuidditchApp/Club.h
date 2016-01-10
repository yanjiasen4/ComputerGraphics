#pragma once
#ifndef __CLUB_H__
#define __CLUB_H__
#include "glhf.h"
#include "matrix.h"

const float club_start_y = -29.5f;
const float club_start_x = 0.0f;
const float club_start_z = 1.0f;

class Club
{
public:
	Club();
	~Club();

	void init();
	void update(float x, float y);
	void render();

	void rotate(float angle, float x, float y); // rotate by motherball
	void hit(float force);
	float getAngle() { return angle; }

private:
	float x, y,z;
	float length;
//	float width;
	float angle;
	float thick;
	float aim_x, aim_y;
	float dir_x, dir_y;
};

#endif