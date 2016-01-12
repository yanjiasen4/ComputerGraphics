#ifndef __ORB_H__
#define __ORB_H__

#include <gl/glew.h>
#include <GL/GLUT.H>
#include <math.h>
#include "table.h"
#include <iostream>
#include "genTexture.h"

using namespace std;

extern const float t_length;
extern const float t_width;
extern const float t_thick;
const float defualt_r = 0.25;
const float m_x = 0.0;
const float m_y = -(t_width / 2 - defualt_r);
const float m_z = 0.4;

static int orb_index = 0;
const Color orb_mat_ambient = { 0.4,0.4,0.4,1 };
const Color orb_mat_diffuse = { 0.4,0.4,0.4,1 };
const Color orb_mat_specluar = { 1.0,1.0,1.0,1 };

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
	void initTexture();
	Point3D getPos();
	float getRadius();

	virtual void init();
	virtual void render();
	virtual void update(); // for 2D
	virtual void update(float z); // for 3D

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
	GLuint texID;
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
