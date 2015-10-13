#include"table.h"

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
	glBegin(GL_QUADS);
	glVertex3f(1.0f, 1.0f, -1.0f);			
	glVertex3f(-1.0f, 1.0f, -1.0f);			
	glVertex3f(-1.0f, 1.0f, 1.0f);			
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);			
	glVertex3f(-1.0f, -1.0f, 1.0f);			
	glVertex3f(-1.0f, -1.0f, -1.0f);			
	glVertex3f(1.0f, -1.0f, -1.0f);			
	glEnd();
}

void Table::update()
{

}