/*
  opengl helper function (not good game have fun)
*/

#pragma once
#include <gl/glew.h>
#include <gl/glut.h>
#include <gl/GLAUX.H>

#include <iostream>

#define TEXTURE_NUM 9

using namespace std;

typedef struct
{
	float r;
	float g;
	float b;
	float alpha;
}Color;

void loadAllTexture();
void initAllTexture();
bool loadTexture(const char *filename, GLuint &texID);
void SetMaterial(GLenum face, GLenum pname, Color color);

AUX_RGBImageRec* loadBMP(const char *filename);