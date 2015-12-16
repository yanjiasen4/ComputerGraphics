#pragma once
#ifndef __FLAG_H__
#define __FLAG_H__

#include "glhf.h"
#include "matrix.h"

#define Y_CTR_NUM 5
#define X_CTR_NUM 2

const GLfloat time_s = 0.1f;

class Flag 
{
public:
	Flag();

	void init();
	void render();
	void update();
	
	void setWind(int level);
	void windUp();
	void windDown();

private:
	GLint nNumPoints;
	GLfloat ctrlPoints[X_CTR_NUM][Y_CTR_NUM][3] = 
	{ 
		{ 
			{ -4.0f, 0.0f, 3.0f },
			{ -2.0f, y_d, 3.0f },
			{ 0.0f, 0.0f, 3.0f},
			{ 2.0f, -y_d, 3.0f},
			{ 4.0f, 0.0f, 3.0f}
		},
		{ 
			{ -4.0f, 0.0f, -3.0f },
			{ -2.0f, y_d, -3.0f },
			{ 0.0f, 0.0f, -3.0f},
			{ 2.0f, -y_d, -3.0f},
			{ 4.0f, 0.0f, -3.0f }
	    }
	};
	GLfloat texpts[2][2][2] = { { { 0.0,0.0 },{ 0.0,1.0 } },{ { 1.0,0.0 },{ 1.0,1.0 } } };
	GLuint tex_ID;
	GLfloat dt;
	int w_level;
	GLfloat post_length, post_radius;
	GLfloat y_d, y_offset;
};

#endif