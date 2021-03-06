#include "physical.h"

CrashList::CrashList()
{
	particles.clear();
	objList.clear();
	Orb motherOrb = Orb(m_x,m_y,m_z,defualt_r,0.0,0.0,0.0);
	motherOrb.setColor(1.0, 1.0, 1.0);
	addObj(motherOrb);
	tb = new Table();
	clb = new Club();
}

CrashList::~CrashList()
{
	if (tb)
		delete tb;
	if (clb)
		delete clb;
}

void CrashList::init()
{
	tb->init();
}

void CrashList::addObj(Orb obj)
{
	objList.push_back(obj);
}

void CrashList::delObj(int index)
{
	vector<Orb>::iterator iter = objList.begin();
	while (iter != objList.end())
	{
		if (iter->getIndex() == index)
		{
			objList.erase(iter);
			return;
		}
		else
		{
			iter++;
		}
	}
}

void CrashList::crash()
{
	unsigned int size = objList.size();
	for (unsigned int i = 0; i < size; i++)
	{
		for (unsigned int j = i+1; j < size; j++)
		{
			if (objList[i].cross(objList[j]))
			{
				Point3D o1 = objList[i].o;
				Point3D o2 = objList[j].o;
				Point3D mid = (o1 + o2) / 2;
				Spark *spk = new Spark(30);
				spk->init(mid.x, mid.y, mid.z);
				spk->activate();
				particles.push_back(spk);
				float dis = getDistance3D(objList[i].o, objList[j].o);
				Vector3D v1 = Vector3D(objList[i].vx, objList[i].vy, objList[i].vz);
				Vector3D v2 = Vector3D(objList[j].vx, objList[j].vy, objList[j].vz);
				Vector3D lig = Vector3D(o1.x - o2.x, o1.y - o2.y, o1.z - o2.z);
				Vector3D v1_proj = v1.project(lig);
				Vector3D v2_proj = v2.project(lig);
				v1 = v1 - v1_proj + v2_proj;
				v2 = v2 - v2_proj + v1_proj;
				objList[i].setSpeed(v1.x, v1.y, v1.z);
				objList[j].setSpeed(v2.x, v2.y, v2.z);
				glutPostRedisplay();
			}
		}
	}
}

void CrashList::hit()
{
	Vector3D m_v;
	float club_ag = clb->getAngle();
	float v_x = cos(club_ag/180*PI);
	float v_y = sin(club_ag/180*PI);
	m_v.set(m_v.x+0.2*v_x, m_v.y+0.2*v_y, 0);
	objList[0].setSpeed(m_v.x,m_v.y,m_v.z);
}

Orb CrashList::getObj(int i)
{
	return objList[i];
}

void CrashList::renderAll()
{
	tb->render();
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i]->render();
	}
	clb->render();
	for (int i = 0; i < objList.size(); i++)
	{
		objList[i].render();
	}
}

void CrashList::updateAll(float dt)
{
	tb->update();
	vector<ParticleSystem*>::iterator iter = particles.begin();
	while(iter != particles.end())
	{
		(*iter)->update(dt);
		if (!(*iter)->isActive())
		{
			ParticleSystem *ps = *iter;
			iter = particles.erase(iter);
			delete ps;
		}
		else
		{
			iter++;
		}
	}
	Point3D aim_o = getMPos();
	clb->update(aim_o.x,aim_o.y);
	for (int i = 0; i < objList.size(); i++)
	{
		Point3D pos = objList[i].getPos();
		if (tb->inHill(pos.x, pos.y))
		{
			float r = objList[i].getRadius();
			float z = tb->getHeight(pos.x, pos.y) + r;
			objList[i].update(z);
		}
		else
		{
			objList[i].update();
		}
	}
}

Point3D CrashList::getMPos()
{
	Orb tmp = objList[0];
	return tmp.o;
}

void CrashList::rotateClb(float angle)
{
	Point3D aim_o = getMPos();
	clb->rotate(angle,aim_o.x,aim_o.y);
}

void CrashList::setGstate(int st)
{
	objList[1].state = st;
}
