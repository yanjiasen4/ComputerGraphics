#pragma once
#include "loadObj.h"

class Terrain : public Object
{
public:
	Terrain();
	Terrain(const char *filename);
	~Terrain();

	void setPos(GLfloat x, GLfloat y, GLfloat z);
	void setAngle(GLfloat ag);
};
