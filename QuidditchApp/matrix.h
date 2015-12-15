#ifndef __MARTIX_H__
#define __MARTIX_H__

#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

#define PI 3.14159265

class Point3D
{
public:
	Point3D() { x = y = z = 0; }
	Point3D(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
	Point3D(Point3D &p) { x = p.x; y = p.y; z = p.z; }

public:
	float x, y, z;
};

float getDistance3D(Point3D p1, Point3D p2);

class Vector3D
{
public:
	Vector3D();
	Vector3D(float xx, float yy, float zz) :x(xx), y(yy), z(zz){}
	Vector3D(Vector3D &v) :x(v.x),y(v.y),z(v.z){}

	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void setX(float xx) { x = xx; }
	void setY(float yy) { y = yy; }
	void setZ(float zz) { z = zz; }
	void set(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }

	Vector3D operator+(Vector3D v);
	Vector3D operator-(Vector3D v);
	Vector3D operator*(Vector3D v);
	Vector3D operator*(float a);

	void rotate(float angle); //向量旋转
	Vector3D cross(Vector3D b); //向量交点
	Vector3D project(Vector3D b); //向量投影
	Vector3D refrection(Vector3D b); //向量折射
	float dot(Vector3D b); //向量内积
	
	float mod(); //取模

	// 向量标准化
	void normalize();
public:
	float x;
	float y;
	float z;
};

#endif