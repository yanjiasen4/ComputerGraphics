/*
  opengl helper function
*/

#pragma once
#include <gl/glut.h>
#include <gl/GLAUX.H>
#include <iostream>

#define TEXTURE_NUM 1

using namespace std;

void loadTexture();
void initTexture();

AUX_RGBImageRec* loadBMP(char *filename);