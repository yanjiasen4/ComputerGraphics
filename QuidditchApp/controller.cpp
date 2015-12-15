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

}



void processSpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		cam->trackup(15.0); // 视角上移15°
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		cam->trackdown(15.0); // 视角下移15°
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