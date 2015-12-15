#include "physical.h"

CrashList::CrashList()
{
	objList.clear();
	Orb motherOrb = Orb(m_x,m_y,m_z,defualt_r,0.0,0.0,0.0);
	motherOrb.setColor(1.0, 1.0, 1.0);
	addObj(motherOrb);
	clb = new Club();
}

CrashList::~CrashList()
{

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
	m_v.set(0.02*v_x, 0.02*v_y, 0);
	objList[0].setSpeed(m_v.x,m_v.y,m_v.z);
}

Orb CrashList::getObj(int i)
{
	return objList[i];
}

void CrashList::renderAll()
{
	clb->render();
	for (int i = 0; i < objList.size(); i++)
	{
		objList[i].render();
	}
}

void CrashList::updateAll()
{
	Point3D aim_o = getMPos();
	clb->update(aim_o.x,aim_o.y);
	for (int i = 0; i < objList.size(); i++)
	{
		objList[i].update();
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
