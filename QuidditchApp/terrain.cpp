#include "terrain.h"

Terrain::Terrain() : Object()
{
}

Terrain::Terrain(const char * filename) : Object()
{
	loadFromObj(filename);
}

Terrain::~Terrain()
{
}

void Terrain::setPos(GLfloat x, GLfloat y, GLfloat z)
{
	position.setX(x);
	position.setY(y);
	position.setZ(z);
}

void Terrain::setAngle(GLfloat ag)
{
	angle = ag;
}
