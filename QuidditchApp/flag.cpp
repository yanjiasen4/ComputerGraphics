#include "flag.h"

Flag::Flag()
{
}

void Flag::init()
{
	tex_ID = 1;
	t = 0;
	post_length = 7.0f;
	post_radius = 0.2;
	w_level = 2;
	setWind(w_level);
}

void Flag::render()
{
	// 保存模型视图矩阵  
	glMatrixMode(GL_MODELVIEW);

	// 绘制旗杆
	glPushMatrix();
	glTranslatef(0.0f, 12.5f, 0.0f);
	glColor3f(0.5f, 0.25f, 0.0f);
	GLUquadric *pObj;
	pObj = gluNewQuadric();
	gluCylinder(pObj, post_radius, post_radius, post_length, 12, 1);
	glPopMatrix();

	// 绘制旗面
	glPushMatrix();
	glTranslatef(3.8f, 12.5f, 8.5f);
	glBindTexture(GL_TEXTURE_2D,20);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glMap2f(GL_MAP2_VERTEX_3,0.0f,10.0f,3,5,0.0f,10.0f,15,2,&ctrlPoints[0][0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0.0f,10.0f,2,2,0.0f,10.0f,4,2,&texpts[0][0][0]);
	glMapGrid2f(10, 0.0f, 10.0f, 10, 0.0f, 10.0f);
	glEvalMesh2(GL_FILL, 0, 10, 0, 10);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_MAP2_VERTEX_3);
	glDisable(GL_MAP2_TEXTURE_COORD_2);
}

void Flag::update(float dt)
{
	// naive implement
	float y, z;
	t += dt;
	float currAngle = t * 120;
	if (currAngle >= 360.0f)
		currAngle -= 360.0f;
	for (int i = 1; i < Y_CTR_NUM; i++)
	{
		y = 0.7*y_d*sin(currAngle /180*PI + i*PI/2)+0.3*y_d*cos(currAngle /180*PI + i*PI/2);
		z = 0.6*z_d*cos(currAngle / 180 * PI + i*PI / 2)+0.4*z_d*sin(currAngle /180*PI+i*PI/2);
		ctrlPoints[0][i][1] = y + y_offset; ctrlPoints[0][i][2] = z + z_offset;
		ctrlPoints[1][i][1] = y + y_offset; ctrlPoints[1][i][2] = -z - z_offset;
	}
}

void Flag::setWind(int level)
{
	y_d = 2.0f + level / 5;
	z_d = 0.8f + level / 10;
	y_offset = 0.5f + level / 10;
	z_offset = 2;
}

void Flag::windUp()
{
	setWind(w_level++);
}

void Flag::windDown()
{
	setWind(w_level--);
}


