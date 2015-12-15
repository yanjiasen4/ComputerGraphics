#ifndef __ORB_H__
#define __ORB_H__

#include <GL/GLUT.H>
#include <math.h>
#include "table.h"
#include <iostream>

using namespace std;

extern const float t_length;
extern const float t_width;
extern const float t_thick;
const float defualt_r = 0.5;
const float m_x = 0.0;
const float m_y = -(t_width / 2 - defualt_r);
const float m_z = 0.0;

static int orb_index = 0;

class Orb
{
public:
	Orb();
	~Orb();
	Orb(Point3D oo, float rr);
	Orb(const Orb &other);
	Orb(float x, float y, float z, float rr);
	Orb(float x, float y, float z, float rr, float speedx, float speedy, float speedz);
	
	int getIndex() { return index; }
	void setSpeed(float speedx, float speedy, float speedz);
	void setColor(float cr, float cg, float cb);
	void setIndex(int ind);

	virtual void init();
	virtual void render();
	virtual void update();

	virtual bool cross(Orb other);
public:
	Point3D o;
	float r;
	float colorR, colorG, colorB;
	float vx, vy, vz;
	float mus;
	int index;
	int state;
	int t;
};

class MotherOrb : public Orb
{

};

class GoldenSnitch : public Orb
{
public:
	GoldenSnitch();
	~GoldenSnitch();

	virtual void init();
	virtual void render();
	virtual void update();

private:
};


#endif
