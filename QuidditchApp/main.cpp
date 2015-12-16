#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include "glhf.h"
#include "controller.h"
#include "table.h"
#include "physical.h"
#include "flag.h"

using namespace std;

const int windowL = 800;
const int windowW = 600;;

GLfloat mat_sp[] = { 1.0,1.0,1.0,1.0 };
GLfloat mat_sh[] = { 50.0 };
GLfloat light_p[] = { 1,1,1,0 };
GLfloat yellow_l[] = { 1,1,0,1 };
GLfloat lmodel_a[] = { 0.1,0.1,0.1,1.0 };
GLfloat spin = 0;
CrashList *crashManager;
Camera *cam;
Controller *control;
Table *tb;
Orb *orb[6];
Orb *ghost[6];
Flag *flag;

void initlights(void)
{
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat position[] = { 0.0, 0.0, 2.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_AUTO_NORMAL);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void InitGL()
{
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	initTexture();
	
	tb = new Table;
	tb->init();
	crashManager = new CrashList();
	orb[0] = new Orb(0.0, 0.0, 0.0, 0.5, 0.003, 0.002, 0.0);
	orb[1] = new Orb(1.0, 0.0, 0.0, 0.5, 0.005, 0.004, 0.0);
	orb[2] = new Orb(0.0, 1.0, 0.0, 0.5, 0.004, -0.006, 0.0);
	orb[3] = new Orb(1.0, 1.0, 0.0, 0.5, 0.008, 0.001, 0.0);
	orb[4] = new Orb(1.0, -1.0, 0.0, 0.5, 0.003, 0.006, 0.0);
	orb[5] = new Orb(-1.0, 0.0, 0.0, 0.5, 0.002, 0.002, 0.0);
	ghost[0] = new Orb(5.0, 4.0, 0.0,0.5, 0, 0, 0);
	ghost[1] = new Orb(0.0, 4.0, 0.0, 0.5, 0, 0, 0);
	ghost[2] = new Orb(-5.0, 4.0, 0.0, 0.5, 0, 0, 0);
	ghost[3] = new Orb(5.0, -4.0, 0.0, 0.5, 0, 0, 0);
	ghost[4] = new Orb(0.0, -4.0, 0.0, 0.5, 0, 0, 0);
	ghost[5] = new Orb(-5.0, -4.0, 0.0, 0.5, 0, 0, 0);
	Orb* gorb = new Orb(0.0, 0.0, 10.0, 0.5, 0, 0.008, 0);
	gorb->setIndex(2);
	gorb->init();
	crashManager->addObj(*gorb);
	for (int i = 0; i < 6; i++)
	{
		orb[i]->init();
		ghost[i]->init();
		crashManager->addObj(*orb[i]);
		crashManager->addObj(*ghost[i]);
	}

	Vector3D pos(0, -23.1495, 86.395);
	Vector3D ref(0, 0.0, 0.0);
	Vector3D vis(0, 0.866025, -0.5);
	control = new Controller(pos, ref, vis);
	glLoadIdentity();
	control->init();
	//glMatrixMode(GL_PROJECTION);
	//glOrtho(-200, 200, -200, 200, 100, 1000);
	flag = new Flag();
	flag->init();
	initlights();
}


void myDisplay()
{
	glClearColor(0.8, 0.8, 0.8, 0);  //设置背景色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	control->setModelViewMatrix();
	tb->render();
	flag->render();
	flag->update();
	crashManager->crash();
	crashManager->renderAll();
	crashManager->updateAll();
	glFlush();
}

void timerProc(int id)
{
	myDisplay();
	glutTimerFunc(16, timerProc, 1);
}

void ChangeSize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	control->setShap(36.0, (GLfloat)w / (GLfloat)h, 10, 150.0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(windowW, windowL);    //显示框大小
	glutInitWindowPosition(200, 400); //确定显示框左上角的位置
	glutCreateWindow("Quidditch");
	InitGL();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(32, timerProc, 1);
	glutMainLoop();
	return 0;
}