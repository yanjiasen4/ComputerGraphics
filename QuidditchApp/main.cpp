#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include "glhf.h"
#include "controller.h"
#include "table.h"
#include "physical.h"
#include "flag.h"
#include "particle.h"

using namespace std;

const int windowL = 800;
const int windowW = 1000;
const float orb_z = 0.4;

GLfloat orb_r = 0.3;
GLfloat spin = 0;
Skybox *skybox;
Spark *ps;
CrashList *crashManager;
Camera *cam;
Controller *control;
//Table *tb;
Orb *orb[6];
Orb *ghost[6];
Flag *flag;

GLfloat light1_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
GLfloat light1_diffuse[] = { 0.4, 0.6, 0.5, 1.0 };
GLfloat light1_specular[] = { 0.4, 0.6, 0.5, 1.0 };
GLfloat light1_position[] = { m_x, m_y, 10.0, 1.0 };
GLfloat light1_spotdir[] = { 0.0, 0.0, -1.0 };
GLfloat light0_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light0_position[] = { 0.0, 10.0, 8.0, 1.0 };
GLfloat light0_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light0_shininess[] = { 50.0 };
GLfloat light1_constan_attenuation[] = { 1.5 };

void initlights(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_AUTO_NORMAL);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 24.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_spotdir);
	glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, light1_constan_attenuation); // 常数衰减
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0); 
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light0_ambient);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light0_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light0_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, light0_shininess);
}

void setlights(void)
{
	Point3D mPos = crashManager->getMPos();
	light1_position[0] = mPos.x;
	light1_position[1] = mPos.y;
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_spotdir);
}

void InitGL()
{
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);	// 设置s方向的纹理自动生成
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);	// 设置t方向的纹理自动生成

	initAllTexture();

	//tb = new Table;
	//tb->init();
	crashManager = new CrashList();
	orb[0] = new Orb(0.0, 0.0, orb_z, orb_r, 0.003, 0.002, 0.0);
	orb[1] = new Orb(1.0, 0.0, orb_z, orb_r, 0.005, 0.004, 0.0);
	orb[2] = new Orb(0.0, 1.0, orb_z, orb_r, 0.004, -0.006, 0.0);
	orb[3] = new Orb(1.0, 1.0, orb_z, orb_r, 0.008, 0.001, 0.0);
	orb[4] = new Orb(1.0, -1.0, orb_z, orb_r, 0.003, 0.006, 0.0);
	orb[5] = new Orb(-1.0, 0.0, orb_z, orb_r, 0.002, 0.002, 0.0);
	ghost[0] = new Orb(5.0, 4.0, orb_z, orb_r, 0, 0, 0);
	ghost[1] = new Orb(0.0, 4.0, orb_z, orb_r, 0, 0, 0);
	ghost[2] = new Orb(-5.0, 4.0, orb_z, orb_r, 0, 0, 0);
	ghost[3] = new Orb(5.0, -4.0, orb_z, orb_r, 0, 0, 0);
	ghost[4] = new Orb(0.0, -4.0, orb_z, orb_r, 0, 0, 0);
	ghost[5] = new Orb(-5.0, -4.0, orb_z, orb_r, 0, 0, 0);
	Orb* gorb = new Orb(0.0, 0.0, 10.0, orb_r, 0, 0.008, 0);
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
	crashManager->init();

	Vector3D pos(0, -10, 40);
	Vector3D ref(0, 0.0, 0.0);
	Vector3D vis(0, 0.866025, -0.5);
	skybox = new Skybox(0, -10, 40);
	skybox->init();
	control = new Controller(pos, ref, vis);
	glLoadIdentity();
	control->init();
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
	setlights();
	skybox->render();
	//tb->render();
	flag->render();

	flag->update();
	crashManager->crash();
	crashManager->renderAll();
	crashManager->updateAll();

	glutSwapBuffers();
	glFlush();
	//cout << glGetError() << endl;
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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowW, windowL);    //显示框大小
	glutInitWindowPosition(600, 400);        //确定显示框左上角的位置
	glutCreateWindow("Quidditch");
	InitGL();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(16, timerProc, 1);
	glutMainLoop();
	return 0;
}