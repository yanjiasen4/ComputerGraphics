#pragma once
#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <gl/glew.h>
#include <gl\glut.h>
#include "camera.h"
#include "flag.h"
#include "physical.h"
using namespace std;

extern Skybox *skybox;
extern Camera *cam;
extern Flag  *flag;
extern CrashList *crashManager;
extern const int windowL;
extern const int windowW;
const int windowOx = windowW / 2;
const int windowOy = windowL / 2;

float getClubAngle(int x, int y);

class Controller
{
public:
	Controller();
	Controller(Vector3D pos, Vector3D ref, Vector3D V);
	~Controller();
	void init();
	void start();

	void setModelViewMatrix();
	void setShap(float viewAngle, float aspect, float Near, float Far);
private:
	void initKeyboard();
	void initMouse();
};

#endif  __KEYBOARD_H__