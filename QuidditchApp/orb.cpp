#include "orb.h"

Orb::Orb()
{
	o = Point3D(0, 0, 0);
	r = 1.0f;
}

Orb::~Orb()
{

}

Orb::Orb(Point3D oo, float rr) : o(oo), r(rr)
{
}

Orb::Orb(float x, float y, float z, float rr)
{
	Point3D oo(x, y, z);
	o = oo;
	r = rr;
}

void Orb::init()
{

}

void Orb::render()
{
	glPushMatrix();
	glTranslatef(o.x, o.y, o.z);
	glutSolidSphere(r, 30, 30);
	glPopMatrix();
	glFlush();
}

void Orb::update()
{
	o.x += vx;
	o.y += vy;
	o.z += vz;
	// Óë×À×Ó±ßÑØµÄÅö×²¼ì²â
	if (o.x > t_length / 2 || o.x < -t_length / 2)
	{
		vx = -vx;
		o.x = t_length - o.x;
	}
	if (o.y > t_width / 2 || o.x < -t_width / 2)
	{
		vy = -vy;
		o.y = t_width - o.y;
	}
}



