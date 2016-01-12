#include "controller.h"

bool spotOpen = true;

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
	initMouse();
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

void processMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		crashManager->hit();
		glutPostRedisplay();
	}
}

void processMouseMove(int x, int y)
{
	int dx = x - windowOx;
	int dy = y - windowOy;
	float dis = sqrt((float)(dx*dx + dy*dy));
	float angle = 180*asin((float)dy / dis)/PI;
	if (dx < 0 && dy > 0 && angle > 0 && angle < 90) // 2nd quadrant
	{
		angle = 180 - angle;
	}
	else if (dx < 0 && dy < 0) // 4th quadrant 
	{
		angle -= 90;
	}
	crashManager->rotateClb(angle);
	//cout << "x:" << x << " " << "y:" << y << "\n";
	//crashManager->rotateClb(getClubAngle(x, y));
}


void processNormalKeys(unsigned char key, int x, int y)
{
	Point3D newVis;
	switch (key) {
	case 'u':
		flag->windUp();
		glutPostRedisplay();
		break;
	case 'i':
		flag->windDown();
		glutPostRedisplay();
		break;
	case 'r':
		cam->resetCamera();
		glutPostRedisplay();
		break;
	case 'z':
		newVis = cam->zoomin(1);
		skybox->update(newVis.x, newVis.y, newVis.z);
		glutPostRedisplay();
		break;
	case 'x':
		newVis = cam->zoomout(1);
		skybox->update(newVis.x, newVis.y, newVis.z);
		glutPostRedisplay();
		break;
	case 'b':
		if (spotOpen)
		{
			glDisable(GL_LIGHT1);
			spotOpen = false;
		}
		else {
			glEnable(GL_LIGHT1);
			spotOpen = true;
		}
		break;
	default:
		break;
	}
}

void processSpecialKeys(int key, int x, int y)
{
	Point3D newVis;
	switch (key) {
	case GLUT_KEY_UP:
		newVis = cam->trackup(1.0); //  ”Ω«…œ“∆1°„
		cout << newVis.x << newVis.y << newVis.z << endl;
		skybox->update(newVis.x, newVis.y, newVis.z);
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		newVis = cam->trackdown(1.0); //  ”Ω«œ¬“∆1°„
		cout << newVis.x << newVis.y << newVis.z << endl;
		skybox->update(newVis.x, newVis.y, newVis.z);
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT: //  ”Ω«◊Û–˝1°„
		newVis = cam->turnleft(1.0);
		cout << newVis.x << newVis.y << newVis.z << endl;
		skybox->update(newVis.x, newVis.y, newVis.z);
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT: //  ”Ω«”“–˝1°„
		newVis = cam->turnright(1.0);
		cout << newVis.x << newVis.y << newVis.z << endl;
		skybox->update(newVis.x, newVis.y, newVis.z);
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

void Controller::initMouse()
{
	glutMouseFunc(processMouseClick);
	glutPassiveMotionFunc(processMouseMove);
}

float getClubAngle(int x, int y)
{
	return 0;
}