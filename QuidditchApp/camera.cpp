#include "camera.h"

Camera::Camera(Vector3D pos, Vector3D tar,  Vector3D V) :
view(pos), ref(tar), vis(V)
{
	Vector3D upv(vis.x - view.x, vis.y - view.y, vis.z - view.z);
	zxangle = atan(0.0);
	xyangle = atan(pos.x / pos.x);

	n.set(view.x - ref.x, view.y - ref.y, view.z - ref.z);
	u.set(upv.cross(n).x, upv.cross(n).y, upv.cross(n).z);
	v.set(n.cross(u).x, n.cross(u).y, n.cross(u).z);

	// 标准化向量
	n.normalize();
	u.normalize();
	v.normalize();
	setModelViewMatrix();
}

void Camera::setModelViewMatrix()
{
	/*
	float m[16];
	Vector3D eVec(view.x, view.y, view.z);
	m[0] = u.x; m[4] = u.y; m[8] = u.z; m[12] = -eVec.dot(u);
	m[1] = v.x; m[5] = v.y; m[9] = v.z; m[13] = -eVec.dot(v);
	m[2] = n.x; m[6] = n.y; m[10] = n.z;m[14] = -eVec.dot(n);
	m[3] = 0;   m[7] = 0;   m[11] = 0;  m[15] = 1.0;
	*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(view.x,view.y,view.z, ref.x,ref.y,ref.z, 0,0,1);
	//glLoadMatrixf(m);     //用M矩阵替换原视点矩阵  
}

void Camera::setShape(float viewAngle, float aspect, float Near, float Far)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                                   //设置当前矩阵模式为投影矩阵并归一化  
	gluPerspective(viewAngle, aspect, Near, Far);       //对投影矩阵进行透视变换  
}

void Camera::setCamera()
{
	Vector3D upv(vis.x - view.x, vis.y - view.y, vis.z - view.z);

	n.set(view.x - ref.x, view.y - ref.y, view.z - ref.z);
	u.set(upv.cross(n).x, upv.cross(n).y, upv.cross(n).z);
	v.set(n.cross(u).x, n.cross(u).y, n.cross(u).z);

	// 标准化向量
	n.normalize();
	u.normalize();
	v.normalize();
	setModelViewMatrix();
}

void Camera::resetCamera()
{
	view.setX(0);
	view.setY(-10);
	view.setZ(40);
	setCamera();
}

Point3D Camera::trackup(float angle)
{
	Vector3D nview = view;
	zxangle += angle;
	float radius = getDistance();
	float cs = cos(zxangle*PI/180);
	float sn = sin(zxangle*PI/180);
	view.setY(radius * sn);
	view.setZ(radius * cs);
	vis.setY(cs);
	vis.setZ(sn);
	setCamera();
	// debug
	//printCamInfo();
	// reflush
	setModelViewMatrix();
	return Point3D(vis.x, vis.y, vis.z);
}

Point3D Camera::trackdown(float angle)
{
	Vector3D nview = view;
	zxangle -= angle;
	float radius = getDistance();
	float cs = cos(zxangle*PI / 180);
	float sn = sin(zxangle*PI / 180);
	view.setY(radius * sn);
	view.setZ(radius * cs);
	vis.setY(cs);
	vis.setZ(sn);
	setCamera();
	// debug
	//printCamInfo();
	// reflush
	setModelViewMatrix();
	return Point3D(view.x, view.y, view.z);
}

Point3D Camera::turnleft(float offset)
{
	float x = view.x;
	float y = view.y;
	float r = sqrt(x*x + y*y);
	float cs = acos(x / r)*180/PI;
	cs += offset;
	if (y < 0)
	{
		cs = -cs;
	}
	x = r*cos(cs*PI/180);
	y = r*sin(cs*PI/180);
	view.setX(x);
	view.setY(y);
	setCamera();
	// debug
	//printCamInfo();
	// reflush
	setModelViewMatrix();
	return Point3D(view.x, view.y, view.z);
}

Point3D Camera::turnright(float offset)
{
	float x = view.x;
	float y = view.y;
	float r = sqrt(x*x + y*y);
	float cs = acos(x / r) * 180 / PI;
	cs -= offset;
	if (y < 0)
	{
		cs = -cs;
	}
	x = r*cos(cs*PI / 180);
	y = r*sin(cs*PI / 180);
	view.setX(x);
	view.setY(y);
	// debug
	//printCamInfo();
	// reflush
	setModelViewMatrix();
	return Point3D(view.x, view.y, view.z);
}

Point3D Camera::zoomin(float offset)
{
	float y = view.y;
	y -= offset;
	view.setY(y);
	setCamera();
	// debug
	//printCamInfo();
	// reflush
	setModelViewMatrix();
	return Point3D(view.x, view.y, view.z);
}

Point3D Camera::zoomout(float offset)
{
	float y = view.y;
	y += offset;
	view.setY(y);
	setCamera();
	// debug
	//printCamInfo();
	// reflush
	setModelViewMatrix();
	return Point3D(view.x, view.y, view.z);
}

float Camera::getDistance()
{
	return sqrt(view.x*view.x + view.y*view.y + view.z*view.z);
}

void Camera::up(float dx)
{
	view.setX(view.getX() + dx);
}
void Camera::down(float dx)
{
	view.setX(view.getX() - dx);
}
void Camera::right(float dy)
{
	view.setY(view.getY() + dy);
}
void Camera::left(float dy)
{
	view.setY(view.getY() - dy);
}
void Camera::forward(float dz)
{
	view.setZ(view.getZ() + dz);
}
void Camera::back(float dz)
{
	view.setZ(view.getZ() - dz);
}

void Camera::printCamInfo()
{
	cout << "at:";
	view.printV();
	cout << endl << "look at:";
	ref.printV();
	cout << endl << "v:";
	vis.printV();
	cout << endl;
}