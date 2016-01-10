#pragma once
#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "glhf.h"

#define EMAX 75

#define BACK_TEX  2
#define DOWN_TEX  3
#define FRONT_TEX 4
#define LEFT_TEX  5
#define RIGHT_TEX 6
#define UP_TEX    7

class Skybox
{
public:
	Skybox();
	Skybox(GLfloat xx, GLfloat yy, GLfloat zz);
	~Skybox();

	void init();
	void update(GLfloat xx, GLfloat yy, GLfloat zz);
	void render();

private:
	GLfloat x, y, z;
	GLfloat vertex[8][3] = {
		-EMAX, -EMAX, -EMAX,
		 EMAX, -EMAX, -EMAX,
		-EMAX,  EMAX, -EMAX,
		 EMAX,  EMAX, -EMAX,
		-EMAX, -EMAX,  EMAX,
		 EMAX, -EMAX,  EMAX,
		-EMAX,  EMAX,  EMAX,
		 EMAX,  EMAX,  EMAX
	};
	GLint index_list[6][4] = {
		0,2,3,1,
		0,4,6,2,
		0,1,5,4,
		4,5,7,6,
		1,3,7,5,
		2,6,7,3
	};
};

#endif