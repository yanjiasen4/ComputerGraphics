#include "flag.h"

Flag::Flag()
{
}

void Flag::init()
{
	tex_ID = 1;
	dt = 0;
	post_length = 7.0f;
	post_radius = 0.2;
	w_level = 2;
	setWind(w_level);
}

void Flag::render()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 保存模型视图矩阵  
	glMatrixMode(GL_MODELVIEW);

	// 绘制旗杆
	glPushMatrix();
	glTranslatef(0.0f, 24.0f, 0.0f);
	glColor3f(0.5f, 0.25f, 0.0f);
	GLUquadric *pObj;
	pObj = gluNewQuadric();
	gluCylinder(pObj, post_radius, post_radius, post_length, 12, 1);
	glPopMatrix();

	// 绘制旗面
	glPushMatrix();
	glTranslatef(3.8f, 24.0f, 8.5f);
	glBindTexture(GL_TEXTURE_2D, tex_ID);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glMap2f(GL_MAP2_VERTEX_3,0.0f,10.0f,3,5,0.0f,10.0f,15,2,&ctrlPoints[0][0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0.0f,10.0f,2,2,0.0f,10.0f,4,2,&texpts[0][0][0]);
	glMapGrid2f(10, 0.0f, 10.0f, 10, 0.0f, 10.0f);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEvalMesh2(GL_FILL, 0, 10, 0, 10);
	glPopMatrix();
	glutSwapBuffers();
	glDisable(GL_TEXTURE_2D);
}

void Flag::update()
{
	// naive implement
	float y;
	dt += time_s;
	if (dt >= 360.0f)
		dt -= 360.0f;
	for (int i = 1; i < Y_CTR_NUM; i++)
	{
		y = y_d*sin(dt/180*PI + i*PI/2);
		ctrlPoints[0][i][1] = y + y_offset;
		ctrlPoints[1][i][1] = y + y_offset;
	}
}

void Flag::setWind(int level)
{
	y_d = 1.0f + level / 5;
	y_offset = 0.5f + level / 10;
}

void Flag::windUp()
{
	setWind(w_level++);
}

void Flag::windDown()
{
	setWind(w_level--);
}


