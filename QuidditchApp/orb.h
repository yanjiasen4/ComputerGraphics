#ifndef __ORB_H__
#define __ORB_H__

#include <GL/GLUT.H>
#include <math.h>
#include "matrix.h"
#include "table.h"

extern const float t_length;
extern const float t_width;
extern const float t_thick;

class Orb
{
public:
	Orb();
	~Orb();
	Orb(Point3D oo, float rr);
	Orb(float x, float y, float z, float rr);

	virtual void init();
	virtual void render();
	virtual void update();
private:
	Point3D o;
	float r;
	float colorR, colorG, colorB;
	float vx, vy, vz;
};


#endif
