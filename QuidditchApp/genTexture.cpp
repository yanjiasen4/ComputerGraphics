#include "genTexture.h"

Texture* genTexture(int seed)
{
	Texture *tex = new Texture();
	tex->sizeX = TEX_X;
	tex->sizeY = TEX_Y;
	tex->data = new unsigned char[TEX_X*TEX_Y * 3];
	for (int i = 0; i < TEX_Y; i++)
	{
		for (int j = 0; j < TEX_X; j++)
		{
			unsigned char value = LEVEL*perlinNoise(float(j+seed)/16, float(i+seed)/16);
			tex->data[(j + i*TEX_X) * 3]     = 0;
			tex->data[(j + i*TEX_X) * 3 + 1] = 0;
			tex->data[(j + i*TEX_X) * 3 + 2] = value;
		}
	}
	return tex;
}