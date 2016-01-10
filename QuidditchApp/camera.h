#pragma once
#ifndef __CEMERA_H__ 
#define __CAMERA_H__

#include <gl/glew.h>
#include <GL\GLUT.H>
#include "matrix.h"
#include "skybox.h"

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
	void resetCamera();

	// -------视角轨道滑动---------
	Point3D trackup(float angle);
	Point3D trackdown(float angle);
	Point3D turnleft(float angle);
	Point3D turnright(float angle);
	Point3D zoomin(float offset);
	Point3D zoomout(float offset);

	// -------视角平移操作---------
	void up(float dx);
	void down(float dx);
	void right(float dy);
	void left(float dy);
	void forward(float dz);
	void back(float dz);

	// ------- for debug ----------
	void printCamInfo();

private:
	//Skybox *skybox;
	Vector3D view;
	Vector3D ref;
	Vector3D vis;
	Vector3D u, v, n;
	float zxangle, xyangle;
};


#endif