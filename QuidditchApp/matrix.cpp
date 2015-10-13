#include"matrix.h"

Vector3D::Vector3D()
{
	x = y = z = 0;
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

float Vector3D::dot(Vector3D b)
{
	return x*b.x + y*b.y + z*b.z;
}

Vector3D Vector3D::operator+(Vector3D v)
{
	return Vector3D(this->x + v.getX(), this->y + v.getY(), this->z + v.getZ());
}

Vector3D Vector3D::operator-(Vector3D v)
{
	return Vector3D(this->x - v.getX(), this->y - v.getY(), this->z - v.getZ());
}

float Vector3D::operator*(Vector3D v)
{
	return (this->x * v.getX() + this->y * v.getY() + this->z * v.getZ());
}

void Vector3D::normalize()
{
	float psum = sqrt(x*x + y*y + z*z);
	set(x / psum, y / psum, z / psum);
}

