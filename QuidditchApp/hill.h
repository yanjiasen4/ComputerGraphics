#pragma once
#ifndef __HILL_H__
#define __HILL_H__

#include "loadObj.h"

const float hillX_max = 20.0f;

class Hill : public Object
{
public:
	Hill();
	Hill(const char *filename);
	~Hill();

	void init();
	void setAngle(GLfloat ag);
	bool inHill(float x, float y);
	float getHeight(float x, float y);

private:
	void calcHeight();

private:
	float xmin, xmax, ymin, ymax;
	float **heightDiagram;
};

#endif