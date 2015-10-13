#include "controller.h"

Controller::Controller()
{
	//.......
}

Controller::Controller(Vector3D pos, Vector3D ref, Vector3D V)
{
	cam = new Camera(pos,ref,V);
	setModelViewMatrix();
}

Controller::~Controller()
{
	if (cam)
	{
		delete cam;
	}
}

void Controller::init()
{
	initKeyboard();
}

void Controller::start()
{
}

void Controller::setModelViewMatrix()
{
	cam->setModelViewMatrix();
}

void Controller::setShap(float viewAngle, float aspect, float Near, float Far)
{
	cam->setShape(viewAngle, aspect, Near, Far);
}

void processNormalKeys(unsigned char key, int x, int y)
{

}



void processSpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		cam->trackup(15.0);
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		cam->trackdown(15.0);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void Controller::initKeyboard()
{
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
}
