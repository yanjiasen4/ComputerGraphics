#pragma once
#ifndef __CEMERA_H__ 
#define __CAMERA_H__

#include <GL\GLUT.H>
#include "matrix.h"

#include <iostream>

using namespace std;

class Camera 
{
public:
	Camera() {};
	Camera(Vector3D pos, Vector3D tar, Vector3D V);
	float getDistance();
	void setModelViewMatrix();
	void setShape(float viewAngle, float aspect, float Near, float Far);
	void setCamera();

	// -------视角轨道滑动---------
	void trackup(float angle);
	void trackdown(float angle);

	// -------视角平移操作---------
	void up(float dx);
	void down(float dx);
	void right(float dy);
	void left(float dy);
	void forward(float dz);
	void back(float dz);

private:
	Vector3D view;
	Vector3D ref;
	Vector3D vis;
	Vector3D u, v, n;
	float zxangle;
};


#endif