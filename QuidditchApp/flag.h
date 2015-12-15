#pragma once
#ifndef __FLAG_H__
#define __FLAG_H__

#include "glhf.h"

class Flag 
{
public:
	Flag();

	void init();
	void render();
	void update();

private:
	GLint nNumPoints;
	GLfloat ctrlPoints[3][3][3] = 
	{ 
		{ 
			{ -4.0f, 0.0f, 4.0f },
			{ -2.0f, 4.0f, 4.0f },
			{ 4.0f, 0.0f, 4.0f } 
		},
		{ 
			{ -4.0f, 0.0f, 0.0f },
			{ -2.0f, 4.0f, 0.0f },
			{ 4.0f, 0.0f, 0.0f } 
	    },
		{ 
			{ -4.0f, 0.0f, -4.0f },
			{ -2.0f, 4.0f, -4.0f },
			{ 4.0f, 0.0f, -4.0f } 
		} 
	};
	GLfloat texpts[2][2][2] = { { { 0.0,0.0 },{ 0.0,1.0 } },{ { 1.0,0.0 },{ 1.0,1.0 } } };
	GLuint tex_ID;
	GLfloat post_length, post_radius;
};

#endif