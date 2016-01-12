#include "skybox.h"

Skybox::Skybox()
{
	x = y = 0.0f;
}

Skybox::Skybox(GLfloat xx, GLfloat yy, GLfloat zz)
{
	x = xx;
	y = yy;
	z = zz;
}

Skybox::~Skybox()
{
}

void Skybox::init()
{
	
}

void Skybox::update(GLfloat xx, GLfloat yy, GLfloat zz)
{
	x = xx;
	y = yy;
	z = zz;
}

void Skybox::render()
{
	glPushMatrix();

	// 移动到初始视点的位置
	glTranslatef(x, y, z);
	glRotatef(90, 1.0, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, DOWN_TEX);
	// 下
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-EMAX, EMAX, -EMAX);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-EMAX, EMAX,  EMAX);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( EMAX, EMAX,  EMAX);  	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( EMAX, EMAX, -EMAX);	
	glEnd();

	// 上
	glBindTexture(GL_TEXTURE_2D, UP_TEX);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-EMAX, -EMAX, -EMAX);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-EMAX, -EMAX,  EMAX);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( EMAX, -EMAX,  EMAX);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( EMAX, -EMAX, -EMAX);
	glEnd();

	// 前
	glBindTexture(GL_TEXTURE_2D, FRONT_TEX);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-EMAX, -EMAX,  EMAX);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( EMAX, -EMAX,  EMAX);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( EMAX,  EMAX,  EMAX);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-EMAX,  EMAX,  EMAX);
	glEnd();
	
	// 后
	glBindTexture(GL_TEXTURE_2D, BACK_TEX);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-EMAX, -EMAX, -EMAX);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( EMAX, -EMAX, -EMAX);
		glTexCoord2f(1.0f, 0.0f); glVertex3f (EMAX,  EMAX, -EMAX);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-EMAX,  EMAX, -EMAX);
	glEnd();
	

	// 左
	glBindTexture(GL_TEXTURE_2D, LEFT_TEX);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-EMAX, -EMAX, -EMAX);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-EMAX, -EMAX,  EMAX);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-EMAX,  EMAX,  EMAX);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-EMAX,  EMAX, -EMAX);
	glEnd();
	

	// 右
	glBindTexture(GL_TEXTURE_2D, RIGHT_TEX);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( EMAX, -EMAX, -EMAX);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( EMAX, -EMAX,  EMAX);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( EMAX,  EMAX,  EMAX);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( EMAX,  EMAX, -EMAX);
	glEnd();

	glPopMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	
}



