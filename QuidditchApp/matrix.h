#ifndef __MARTIX_H__
#define __MARTIX_H__

#include <math.h>

#define PI 3.14159265

class Point3D
{
public:
	Point3D() { x = y = z = 0; }
	Point3D(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
	float x, y, z;
};


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
	float   operator*(Vector3D v);

	Vector3D cross(Vector3D b);
	float dot(Vector3D b);

	// 向量标准化
	void normalize();
public:
	float x;
	float y;
	float z;
};

#endif