#pragma once
#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "glhf.h"
#include "matrix.h"
#include <vector>
#include <time.h>

using namespace std;

#define TEX_PARTICLE 8

static Color colors[12] =		// Rainbow Of Colors
{
	{ 1.0f,0.5f,0.5f },{ 1.0f,0.75f,0.5f },{ 1.0f,1.0f,0.5f },{ 0.75f,1.0f,0.5f },
	{ 0.5f,1.0f,0.5f },{ 0.5f,1.0f,0.75f },{ 0.5f,1.0f,1.0f },{ 0.5f,0.75f,1.0f },
	{ 0.5f,0.5f,1.0f },{ 0.75f,0.5f,1.0f },{ 1.0f,0.5f,1.0f },{ 1.0f,0.5f,0.75f }
};


class Particle
{
public:
	Particle() {};
	Particle(Vector3D vp, Vector3D vv, Vector3D va, Color cl, float ag, float lf, float sz);
	Particle(float x, float y, float z, float sx, float sy, float sz, float ax, float ay, float az, float cr, float cg, float cb, float ag, float lf, float r);
	Particle(const Particle &p) { position = p.position; velocity = p.velocity; acceleration = p.acceleration; color = p.color; age = p.age; life = p.life; size = p.size; active = true; }
	Vector3D position;
	Vector3D velocity;
	Vector3D acceleration;
	Color color;
	float age;
	float life;
	float size;
	bool active;
};

class ParticleSystem
{
public:
	ParticleSystem(int pCount);
	~ParticleSystem();
	virtual void init(GLfloat xx, GLfloat yy, GLfloat zz);
	virtual void update(float dt);
	virtual void render();
	void activate();

	void applyGravity();
	virtual void aging(float dt);
	bool isActive();
	vector<Particle*> particles;
	GLUquadricObj *mySphere;

protected:
	bool active;
	int epcho;
	int pCount;
	GLfloat x, y, z;
};

class Spark : public ParticleSystem
{
public:
	Spark(int pCount) :ParticleSystem(pCount) {};
	~Spark();
	virtual void init(GLfloat xx, GLfloat yy, GLfloat zz);
	virtual void update(float dt);
	virtual void render();
	
	virtual void aging(float dt);
	vector<Particle*> particles;
};

class Comet : public ParticleSystem
{

};

#endif