#include"matrix.h"

Vector3D::Vector3D()
{
	x = y = z = 0;
}

void Vector3D::rotate(float angle)
{
	float old_x = x;
	float old_y = y;
	x = old_x*cos(angle) - old_y*sin(angle);
	y = old_x*sin(angle) + old_y*cos(angle);
}

Vector3D Vector3D::cross(Vector3D b)
{
	float x1, y1, z1;
	x1 = y*b.z - z*b.y;
	y1 = z*b.x - x*b.z;
	z1 = x*b.y - y*b.x;
	Vector3D c(x1, y1, z1);
	return c;
}

// 计算向量在向量b上的投影
Vector3D Vector3D::project(Vector3D b)
{
	return b*(this->dot(b) / (b.mod()*b.mod()));
}

// 其实是2D的......
Vector3D Vector3D::refrection(Vector3D b) 
{
	float theta = acos((this->dot(b)) / (this->mod()*b.mod()));
	Vector3D newV = Vector3D(x, y, z);
	newV.rotate(2 * (PI / 2 - theta));
	return newV;
}

float Vector3D::dot(Vector3D b)
{
	return x*b.x + y*b.y + z*b.z;
}

float Vector3D::mod()
{
	return sqrt(x*x + y*y + z*z);
}

Vector3D Vector3D::operator+(Vector3D v)
{
	return Vector3D(this->x + v.getX(), this->y + v.getY(), this->z + v.getZ());
}

Vector3D Vector3D::operator-(Vector3D v)
{
	return Vector3D(this->x - v.getX(), this->y - v.getY(), this->z - v.getZ());
}

Vector3D Vector3D::operator*(Vector3D v)
{
	return Vector3D(this->x * v.getX(), this->y * v.getY(), this->z * v.getZ());
}

Vector3D Vector3D::operator*(float a)
{
	Vector3D p(x*a, y*a, z*a);
	return p;
}

void Vector3D::normalize()
{
	float psum = sqrt(x*x + y*y + z*z);
	set(x / psum, y / psum, z / psum);
}

float getDistance3D(Point3D p1, Point3D p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}