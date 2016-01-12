#include "glhf.h"

GLuint texture[TEXTURE_NUM];

// load n bmp to opengl which n equals to TEXTURE_NUM
void loadAllTexture()
{
	static char * const texFileName[] = {
		"res/flag.bmp",
		"res/TropicalSunnyDayBack2048.bmp",
		"res/TropicalSunnyDayDown2048.bmp",
		"res/TropicalSunnyDayFront2048.bmp",
		"res/TropicalSunnyDayLeft2048.bmp",
		"res/TropicalSunnyDayRight2048.bmp",
		"res/TropicalSunnyDayUp2048.bmp",
		"res/Particle.bmp",
	};
	AUX_RGBImageRec* TextureImage[TEXTURE_NUM];
	memset(TextureImage, 0, sizeof(void *) * 1);
	for (int i = 0; i < TEXTURE_NUM; i++)
	{
		if (TextureImage[i] = loadBMP(texFileName[i])) {
			glGenTextures(1, &texture[i]);
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, TextureImage[i]->sizeX, TextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
		}
		else {
			cout << "can't open resource file!" << endl;
		}
		if (TextureImage[i]) {
			if (TextureImage[i]->data) {
				free(TextureImage[i]->data);
			}
			free(TextureImage[i]);
			cout << "free texture file " <<i+1<<": "<<texFileName[i]<< endl;
		}
	}
}

void initAllTexture()
{
	loadAllTexture();
}

bool loadTexture(const char *filename, GLuint &texID)
{
	AUX_RGBImageRec* TextureImage[1];
	memset(TextureImage, 0, sizeof(void *) * 1);
	if (TextureImage[0] = loadBMP(filename)) {
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}
	else {
		cout << "can't open resource file!" << endl;
		return false;
	}
	if (TextureImage[0]) {
		if (TextureImage[0]->data) {
			free(TextureImage[0]->data);
		}
		free(TextureImage[0]);
		cout << "free texture file " << texID<<" : "<< filename << endl;
	}
	return true;
}

bool loadTexture(Texture *tex, GLuint &texID)
{
	if (tex != NULL)
	{
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, tex->sizeX, tex->sizeY, 0, GL_BGR, GL_UNSIGNED_BYTE, tex->data);
		if(tex->data)
			delete tex->data;
	}
	else {
		cout << "error texture input!" << endl;
		return false;
	}
}

void SetMaterial(GLenum face, GLenum pname, Color color)
{
	const GLfloat matc[4] = {
		color.r,color.g,color.b,color.alpha
	};
	glMaterialfv(face, pname, matc);
}

// wrapper for auxDIBImageLoad
AUX_RGBImageRec* loadBMP(const char *filename)
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

void fogging()
{
	GLuint filter;						// 使用哪一个纹理过滤器
	GLuint fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR };		// 雾气的模式
	GLuint fogfilter = 0;					// 使用哪一种雾气
	GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };		// 雾的颜色设为白色
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);			// 设置背景的颜色为雾气的颜色
	glFogi(GL_FOG_MODE, fogMode[fogfilter]);		// 设置雾气的模式
	glFogfv(GL_FOG_COLOR, fogColor);			// 设置雾的颜色
	glFogf(GL_FOG_DENSITY, 0.35f);			// 设置雾的密度
	glHint(GL_FOG_HINT, GL_DONT_CARE);			// 设置系统如何计算雾气
	glFogf(GL_FOG_START, 1.0f);				// 雾气的开始位置
	glFogf(GL_FOG_END, 5.0f);				// 雾气的结束位置
	glEnable(GL_FOG);					// 使用雾气
}