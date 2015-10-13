#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <GL\GLUT.H>
#include "controller.h"

using namespace std;

GLfloat mat_sp[] = { 1.0,1.0,1.0,1.0 };
GLfloat mat_sh[] = { 50.0 };
GLfloat light_p[] = { 1,1,1,0 };
GLfloat yellow_l[] = { 1,1,0,1 };
GLfloat lmodel_a[] = { 0.1,0.1,0.1,1.0 };
GLfloat spin = 0;
Camera *cam;
Controller *control;

void InitGL()
{
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_SMOOTH);
	/*glMaterialfv(GL_FRONT, GL_SPECULAR, mat_sp);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_sh);
	glLightfv(GL_LIGHT0, GL_POSITION, light_p); //指定光源的位置
	glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow_l);  //设定漫反射效果
	glLightfv(GL_LIGHT0, GL_SPECULAR, yellow_l); //设定高光反射效果
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_a); //设定全局环境光*/

	glEnable(GL_LIGHTING); //启用光源
	glEnable(GL_LIGHT0);   //使用指定灯光
	glEnable(GL_DEPTH_TEST);
	Vector3D pos(0, 0, 1);
	Vector3D ref(0, 0.0, 0.0);
	Vector3D vis(0, 1, 0);
	control = new Controller(pos, ref, vis);
	glLoadIdentity();
	control->init();

}


void myDisplay()
{
	glClearColor(0, 0, 0, 0);  //设置背景色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 0, 1, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	control->setModelViewMatrix();
	glutWireSphere(0.1, 40, 40);
	glFlush();
}

void ChangeSize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	control->setShap(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(600, 800);    //显示框大小
	glutInitWindowPosition(200, 400); //确定显示框左上角的位置
	glutCreateWindow("Quidditch");
	InitGL();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
	return 0;
}