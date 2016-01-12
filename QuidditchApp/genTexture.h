#ifndef __GENTEXTURE_H__
#define __GENTEXTURE_H__
#pragma once

#include "perlin.h"
#include <iostream>

#define TEX_X 256
#define TEX_Y 256
#define LEVEL 255

class Texture
{
public:
	Texture() { sizeX = sizeY = 0; }
	~Texture() { if (data) { delete[] data; } }
	int sizeX;
	int sizeY;
	unsigned char* data;
};

Texture* genTexture(int seed);

#endif
