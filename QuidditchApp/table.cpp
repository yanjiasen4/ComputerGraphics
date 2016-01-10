#include"table.h"

extern GLuint texture[TEXTURE_NUM];

Table::Table()
{
	terrain = new Terrain("res/mod/terrain.obj");
	terrain->loadMtl("res/mod/terrain.mtl");
	terrain->setAngle(90);
}

Table::~Table()
{
	if(terrain)
		delete terrain;
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
	terrain->draw();
}

void Table::update()
{

}