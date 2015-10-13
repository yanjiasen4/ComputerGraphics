#pragma once
#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <gl\glut.h>
#include "camera.h"

using namespace std;

extern Camera *cam;

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
};

#endif  __KEYBOARD_H__