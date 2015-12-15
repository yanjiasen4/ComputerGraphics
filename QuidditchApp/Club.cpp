#include "Club.h"

Club::Club()
{
	x = club_start_x;
	y = club_start_y;
	z = club_start_z;
	aim_x = club_start_x;
	aim_y = club_start_y - 0.5;
	length = 6.0f;
	angle = 90.0;
}

Club::~Club()
{

}

void Club::init()
{

}

void Club::update(float x, float y)
{
	aim_x = x;
	aim_y = y;
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glRotated(angle, 0, 0, 1);
	//glPopMatrix();
	//glutPostRedisplay();
}

void Club::render()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	float xangle = angle + 90.0;
	float roX = cos(xangle*PI/180);
	float roY = sin(xangle*PI/180);
	glTranslatef(aim_x, aim_y, z);
	glRotated(90, roX, roY, 0);
	glColor3b(99, 99, 0);
	GLUquadricObj *quarobj = gluNewQuadric();
	gluCylinder(quarobj, 0.4, 0.1, length, 60, 60);
	glPopMatrix();
}

void Club::rotate(float ag, float x, float y)
{
	aim_x = x;
	aim_y = y;
	angle = ag;
}

void Club::hit(float force)
{
}
