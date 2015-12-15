#include "orb.h"

Orb::Orb()
{
	o = Point3D(0, 0, 0);
	r = 1.0f;
}

Orb::~Orb()
{

}

Orb::Orb(Point3D oo, float rr) : o(oo), r(rr)
{
}

Orb::Orb(const Orb & other)
{
	o = other.o;
	r = other.r;
	colorR = other.colorR;
	colorG = other.colorG; 
	colorB = other.colorB; 
	vx = other.vx;
	vy = other.vy;
	vz = other.vz;
	index = other.index;
	state = other.state;
	t = other.t;
}

Orb::Orb(float x, float y, float z, float rr)
{
	Point3D oo(x, y, z);
	o = oo;
	r = rr;
	vx = vy = vz = 0;
	state = 0;
	t = 0;
}

Orb::Orb(float x, float y, float z, float rr, float speedx, float speedy, float speedz)
{
	Point3D oo(x, y, z);
	o = oo; 
	r = rr;
	vx = speedx;
	vy = speedy;
	vz = speedz;
	index = 1;
	state = 0;
	t = 0;
}

void Orb::init()
{
	if(index == 2)
	{
		colorR = 1.0;
		colorG = 0.8125;
		colorB = 0.0;
		t = 0;
	}
	else {
		colorR = 0.0;
		colorG = 0.0;
		colorB = 0.0;
	}
}

void Orb::render()
{
	glPushMatrix();
	glTranslatef(o.x, o.y, o.z+r);
	glColor3f(colorR, colorG, colorB);
	glutSolidSphere(r, 30, 30);
	glPopMatrix();
}

void Orb::update()
{
	if (index == 1)
	{
		o.x += vx;
		o.y += vy;
		//o.z += vz;
	}
	else if (index == 2) //golden 
	{
		if (state == 0)
		{
			cout << t << endl;
			vz = 0;
			o.x += vx;
			o.y += vy;
			o.z += vz;
			t++;
			if (t >= 10000 && o.z > 1.0)
			{
				state = 1;
				t = 0;
			}
			else if (t >= 10000 && o.z <= 0.5)
			{
				state = 2;
				t = 0;
			}
		}
		else if (state == 1)
		{
			vz = -0.005;
			o.z += vz;
			if (o.z <= 0.5)
			{
				t = 0;
				state = 0;
			}
		}
		else if (state == 2)
		{
			vz = 0.005;
			o.z += vz;
			if (o.z >= 10)
			{
				state = 0;
			}
		}
	}
	// �����ӱ��ص���ײ���
	if (o.x + r > t_length / 2 || o.x - r < -t_length / 2)
	{
		vx = -vx;
		//o.x = t_length - o.x;
	}
	if (o.y + r > t_width / 2 || o.y - r < -t_width / 2)
	{
		vy = -vy;
		//o.y = t_width - o.y;
	}
	glutPostRedisplay();
}

bool Orb::cross(Orb other)
{
	int timeSlice = 10;
	float curr_dis;
	if ((curr_dis = getDistance3D(o, other.o)) < r + other.r)
	{
		for (int i = 1; i < timeSlice; i++)
		{
			Point3D nextO = Point3D(o.x + i*vx, o.y + i*vy, o.z + i*vz);
			Point3D nextOther = Point3D(other.o.x + i*other.vx, other.o.y + i*other.vy, other.o.z + i*other.vz);
			if (getDistance3D(nextO, nextOther) > curr_dis)
				return false;
			else
				return true;
		}
	}
	else
		return false;
}

void Orb::setSpeed(float speedx, float speedy, float speedz)
{
	vx = speedx; vy = speedy; vz = speedz;
}

void Orb::setColor(float cr, float cg, float cb)
{
	colorG = cr;
	colorG = cg;
	colorB = cb;
}

void Orb::setIndex(int ind)
{
	index = ind;
}

GoldenSnitch::GoldenSnitch()
{
	o = Point3D(0, 0, 10);
	r = 0.5f;
	vx = 0;
	vy = 0.02;
	vz = 0;
	state = 0; // land
}

GoldenSnitch::~GoldenSnitch()
{}


void GoldenSnitch::init()
{
	colorR = 1.0;
	colorG = 0.8125;
	colorB = 0.0;
	t = 0;
}

void GoldenSnitch::render()
{
	glPushMatrix();
	glTranslatef(o.x, o.y, o.z + r);
	glColor3f(colorR, colorG, colorB);
	glutSolidSphere(r, 30, 30);
	glPopMatrix();
}

void GoldenSnitch::update()
{
	if (state == 0)
	{
		cout << t << endl;
		vz = 0;
		o.x += vx;
		o.y += vy;
		o.z += vz;
		t++;
		if (t >= 10000 && o.z > 0)
		{
			state = 1;
			t = 0;
		}
		else if (t >= 10000 && o.z == 0)
		{
			state = 2;
			t = 0;
		}
	}
	else if (state == 1)
	{
		vz = -0.005;
		o.z += vz;
		if (o.z <= 0)
		{
			state = 0;
		}
	}
	else if (state == 2)
	{
		vz = 0.005;
		o.z += vz;
		if (o.z >= 10)
		{
			state = 0;
		}
	}

	// �����ӱ��ص���ײ���
	if (o.x + r > t_length / 2 || o.x - r < -t_length / 2)
	{
		vx = -vx;
	}
	if (o.y + r > t_width / 2 || o.y - r < -t_width / 2)
	{
		vy = -vy;
	}
	glutPostRedisplay();
}
