#include "stringdraw.h"

StringDraw::StringDraw()
{
}

StringDraw::StringDraw(string c)
{
	content = c;
	x = FPS_X;
	y = FPS_Y;
}

StringDraw::~StringDraw()
{
}

void StringDraw::init()
{
}

void StringDraw::render()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-200, 200, -200, 200);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2i(160, 185);
	glDisable(GL_DEPTH_TEST);
	for (int i = 0; i < content.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,content[i]);
	}
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPopMatrix();

}

void StringDraw::update(string c)
{
	setContent(c);
}

void StringDraw::setContent(string c)
{
	content = c;
}
