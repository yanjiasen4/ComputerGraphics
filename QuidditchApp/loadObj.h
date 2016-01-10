#pragma once
#include"glhf.h"
#include<GL\glew.h>
#include"matrix.h"
#include<list>
#include<vector>
#include<string>
#include<sstream>
#include<map>
//#include"textureLoader.h"
#include<fstream>
#include<iostream>
struct Material {
	Color kd;
	Color ka;
	Color ks;
	Color ke;
	GLuint illum;
	GLfloat ns;
	GLuint kd_texid;
	GLuint ka_texid;
};
typedef GLfloat Point[3];
typedef GLfloat UVPoint[2];
typedef GLfloat NMPoint[3];

class SubMesh {
public:
	Point *ptBuffer;
	UVPoint *uvBuffer;
	NMPoint *nmBuffer;
	GLuint vNum;
	GLuint fcNum;
	std::string fcName;
	std::string mtName;
	void draw();
	SubMesh();
	~SubMesh();
};

class Object {
public:
	std::list<SubMesh*> children;
	Point *ptBuffer;
	UVPoint *uvBuffer;
	NMPoint *nmBuffer;
	GLuint vNum;
	GLuint vtNum;
	GLuint vnNum;
	std::map<std::string, Material> material_map;
	Vector3D position;
	GLfloat angle;
	void draw();
	void parsePolygon(std::ifstream&ifs, std::string &name);
	int countFaceNumber(std::ifstream &ifs);
	void countNumber(std::ifstream& ifs);
	void loadMtl(const char*filename);
	void loadFromObj(const char*filename);
	Object();
	~Object();
};