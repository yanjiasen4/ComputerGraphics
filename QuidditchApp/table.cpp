#include"table.h"

extern GLuint texture[TEXTURE_NUM];

Table::Table()
{
	cout << "���س���ģ��" << endl;
	terrain = new Terrain("res/mod/terrain3.obj");
	terrain->loadMtl("res/mod/terrain3.mtl");
	cout << "���ص���ģ��" << endl;
	hill = new Hill("res/mod/hill.obj");
	hill->loadMtl("res/mod/hill.mtl");
	terrain->setAngle(90);
	hill->setAngle(90);
}

Table::~Table()
{
	if(terrain)
		delete terrain;
	if (hill)
		delete hill;
}

void Table::init()
{
	pos.x = pos.y = pos.z = 0;
	length = t_length;
	width = t_width;
	thick = t_thick;
	//terrain->calcHeight();
	hill->init();
}

void Table::render()
{
	terrain->draw();
	hill->draw();
}

void Table::update()
{
	// nothing
}

bool Table::inHill(float x, float y)
{
	return hill->inHill(x, y);
}

float Table::getHeight(float x, float y)
{
	return hill->getHeight(x, y);
}
