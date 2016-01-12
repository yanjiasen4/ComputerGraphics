/*
  opengl helper function (not good game have fun)
*/

#pragma once
#include <gl/glew.h>
#include <gl/glut.h>
#include <gl/GLAUX.H>

#include <iostream>
#include"genTexture.h"

#define TEXTURE_NUM 8

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
bool loadTexture(Texture *tex, GLuint &texID);
void SetMaterial(GLenum face, GLenum pname, Color color);
void fogging();

AUX_RGBImageRec* loadBMP(const char *filename);