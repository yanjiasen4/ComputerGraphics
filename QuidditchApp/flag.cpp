#include "flag.h"

Flag::Flag()
{
}

void Flag::init()
{
	tex_ID = 1;
}

void Flag::render()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ����ģ����ͼ����  
	glMatrixMode(GL_MODELVIEW);

	// �������
	glPushMatrix();
	glTranslatef(0.0f, 24.0f, 0.0f);
	GLUquadric *pObj;
	pObj = gluNewQuadric();
	gluCylinder(pObj, 0.2f, 0.2f, 7.0f, 12, 1);
	glPopMatrix();

	// ��������
	glPushMatrix();
	glTranslatef(3.8f, 24.0f, 8.5f);
	//glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	//glRotatef(60.0f, 1.0f, 0.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, tex_ID);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glMap2f(GL_MAP2_VERTEX_3,0.0f,10.0f,3,3,0.0f,10.0f,9,3,&ctrlPoints[0][0][0]);
	//������ֵ��  
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0.0f,10.0f,2,2,0.0f,10.0f,4,2,&texpts[0][0][0]);
	//��0��10ӳ��һ������10���������  
	glMapGrid2f(10, 0.0f, 10.0f, 10, 0.0f, 10.0f);
	// ��������  
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEvalMesh2(GL_FILL, 0, 10, 0, 10);
	glPopMatrix();
	glutSwapBuffers();
	glDisable(GL_TEXTURE_2D);
}

void Flag::update()
{

}


