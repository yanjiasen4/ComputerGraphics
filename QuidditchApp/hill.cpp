#include "hill.h"

Hill::Hill()
{
	xmin = xmax = ymin = ymax = 0;
}

Hill::Hill(const char * filename)
{
	loadFromObj(filename);
	xmin = ymin = -5000; // small enough
	xmax = ymax = INT_MAX;
	if (!heightDiagram)
	{
		// suppose hill.obj is a matrix
		GLuint num = sqrt(vNum);
		heightDiagram = new float*[num];
		for (int i = 0; i < num; i++)
			heightDiagram[i] = new float[num];
	}
	xmin = 0.0f;
	xmax = 20.0f;
	ymin = -10.0f;
	ymax = 10.0f;
}

Hill::~Hill()
{
	if (heightDiagram)
		delete[] heightDiagram;
}

void Hill::calcHeight()
{
	int px = 0;
	int py = 0;
	for (int i = 0; i < vNum; i++)
	{
		// 为什么手贱旋转了90°
		float x = ptBuffer[i][0];
		float y = ptBuffer[i][2];
		float z = ptBuffer[i][1];
		px = int(x);
		py = int(y)+10;
		heightDiagram[py][px] = z;
	}
}

bool Hill::inHill(float x, float y)
{
	if ((x > xmin && x < xmax) && (y > ymin && y < ymax))
		return true;
	else
		return false;
}

float Hill::getHeight(float x, float y)
{
	if (heightDiagram!=NULL)
	{
		// round to nearest integer
		int px = int(x);
		int py = int(y);
		float b = x - px;
		float a = y - py;
		py += 10;
		float z = (1-a)*((1-b)*heightDiagram[py][px] + b*heightDiagram[py][px + 1]) +  a*((1-b)*heightDiagram[py + 1][px] + b*heightDiagram[py + 1][px + 1]);
		return z;
	}
	else 
	{
		return 0.0f;
	}
}

void Hill::init()
{
	calcHeight();
}

void Hill::setAngle(GLfloat ag)
{
	angle = ag;
}
