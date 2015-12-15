#include"table.h"

extern GLuint texture[TEXTURE_NUM];

Table::Table()
{

}

Table::~Table()
{

}

void Table::init()
{
	pos.x = pos.y = pos.z = 0;
	length = t_length;
	width = t_width;
	thick = t_thick;
}

void Table::render()
{
	glColor3f(0.129f, 0.387f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, t_thick);
	glRectf(-t_length/2, t_width/2, t_length/2, -t_width/2);
	glPopMatrix();
	glEnd();
}

void Table::update()
{

}