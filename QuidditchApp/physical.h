#pragma once

#ifndef __PHYSICAL_H__
#define __PHYSICAL_H__

#include "matrix.h"
#include "orb.h"
#include "Club.h"

#define MORB 0

using namespace std;

class CrashList
{
public:
	CrashList();
	~CrashList();

	void addObj(Orb obj);
	void delObj(int index);
	
	void crash();
	void hit();

	Orb getObj(int i);
	void renderAll();
	void updateAll();

	Point3D getMPos();
	void rotateClb(float angle);

	void setGstate(int st);

private:
	vector<Orb> objList;
	Club *clb;
};

#endif
