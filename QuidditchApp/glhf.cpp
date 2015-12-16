#include "glhf.h"

GLuint texture[TEXTURE_NUM];

// load n bmp to opengl which n equals to TEXTURE_NUM
void loadTexture()
{
	AUX_RGBImageRec* TextureImage[TEXTURE_NUM];
	memset(TextureImage, 0, sizeof(void *) * 1);
	for (int i = 0; i < TEXTURE_NUM; i++)
	{
		if (TextureImage[0] = loadBMP("res/flag.bmp")) {
			glGenTextures(1, &texture[0]);
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else {
			cout << "can't open resource file!" << endl;
		}
		if (TextureImage[0]) {
			if (TextureImage[0]->data) {
				free(TextureImage[0]->data);
			}
			free(TextureImage[0]);
			cout << "free texture file 0" << endl;
		}
	}
}

void initTexture()
{
	loadTexture();
}

// wrapper for auxDIBImageLoad
AUX_RGBImageRec* loadBMP(char *filename)
{
	FILE *File = NULL;
	errno_t err;
	if (!filename) {
		return NULL;
	}
	err = fopen_s(&File, filename, "r");
	if (File) {
		fclose(File);
		return auxDIBImageLoad(filename);
	}
	return NULL;
}